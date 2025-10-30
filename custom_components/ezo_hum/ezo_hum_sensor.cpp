#include "ezo_hum_sensor.h"
#include "esphome/core/log.h"
#include "esphome/core/hal.h"  // for delay()
#include <cstring>
#include <cmath>  // for std::isnan()
#include <algorithm>
#include <vector>
#include <string>

namespace esphome {
namespace ezo_hum {

static const char *const TAG = "ezo_hum";
static const uint8_t EZO_HUM_I2C_ADDR = 0x6F;

void EzoHumSensor::setup() {
  ESP_LOGI(TAG, "EZO-HUM sensor initialized at I2C address 0x%02X", EZO_HUM_I2C_ADDR);
}

bool EzoHumSensor::read_line(std::string &result) {
  uint8_t buffer[32];
  auto err = this->read(buffer, sizeof(buffer));
  if (err != i2c::ERROR_OK) {
    ESP_LOGW(TAG, "I2C read failed: %d", err);
    return false;
  }

  // Convert buffer to ASCII string and trim
  result.assign(reinterpret_cast<char *>(buffer), sizeof(buffer));
  size_t end_pos = result.find('\r');
  if (end_pos != std::string::npos)
    result = result.substr(0, end_pos);
  result.erase(result.find_last_not_of(" \r\n\t") + 1);
  return true;
}

void EzoHumSensor::update() {
  // Send "R" command to request a reading
  const uint8_t cmd[] = {'R'};
  auto err = this->write(cmd, sizeof(cmd));
  if (err != i2c::ERROR_OK) {
    ESP_LOGW(TAG, "I2C write failed: %d", err);
    return;
  }

  // EZO-HUM requires ~1s for measurement
  esphome::delay(1000);

  std::string response;
  if (!this->read_line(response)) {
    ESP_LOGW(TAG, "No response from EZO-HUM");
    return;
  }

  ESP_LOGD(TAG, "Raw response: %s", response.c_str());
  this->parse_reading(response);
}

void EzoHumSensor::parse_reading(const std::string &response) {
  float hum = NAN, temp = NAN, dew = NAN;

  // Make mutable copy and remove CR/LF
  std::string clean = response;
  clean.erase(std::remove_if(clean.begin(), clean.end(),
                             [](unsigned char c){ return c == '\r' || c == '\n'; }),
              clean.end());

  // Split by commas
  std::vector<std::string> tokens;
  size_t start = 0, end = 0;
  while ((end = clean.find(',', start)) != std::string::npos) {
    tokens.push_back(clean.substr(start, end - start));
    start = end + 1;
  }
  tokens.push_back(clean.substr(start));

  // Trim spaces
  auto trim = [](std::string &s){
    size_t first = s.find_first_not_of(" \t");
    size_t last = s.find_last_not_of(" \t");
    if(first == std::string::npos || last == std::string::npos)
      s = "";
    else
      s = s.substr(first, last - first + 1);
  };
  for(auto &t : tokens)
    trim(t);

  // Sanitize numeric tokens
  auto sanitize_number = [](const std::string &s) -> std::string {
    std::string out;
    for(char c : s)
      if((c >= '0' && c <= '9') || c == '.' || c == '-')
        out += c;
    return out;
  };

  if(tokens.size() >= 4) {
    hum = strtof(sanitize_number(tokens[0]).c_str(), nullptr);
    temp = strtof(sanitize_number(tokens[1]).c_str(), nullptr);
    dew = strtof(sanitize_number(tokens[3]).c_str(), nullptr);
  }

  ESP_LOGD(TAG, "Parsed values -> Humidity: %.2f%%  Temp: %.2f°C  Dew: %.2f°C",
           hum, temp, dew);

  if(!std::isnan(hum) && humidity_sensor_ != nullptr)
    humidity_sensor_->publish_state(hum);

  if(!std::isnan(temp) && temperature_sensor_ != nullptr)
    temperature_sensor_->publish_state(temp);

  if(!std::isnan(dew) && dewpoint_sensor_ != nullptr)
    dewpoint_sensor_->publish_state(dew);
}

void EzoHumSensor::dump_config() {
  ESP_LOGCONFIG(TAG, "Atlas Scientific EZO-HUM Sensor:");
  LOG_I2C_DEVICE(this);
  LOG_UPDATE_INTERVAL(this);
  LOG_SENSOR("  ", "Humidity", humidity_sensor_);
  LOG_SENSOR("  ", "Temperature", temperature_sensor_);
  LOG_SENSOR("  ", "Dew Point", dewpoint_sensor_);
}

}  // namespace ezo_hum
}  // namespace esphome