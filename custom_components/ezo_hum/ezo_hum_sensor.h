#pragma once

#include "esphome/core/component.h"
#include "esphome/components/i2c/i2c.h"
#include "esphome/components/sensor/sensor.h"

namespace esphome {
namespace ezo_hum {

class EzoHumSensor : public PollingComponent, public i2c::I2CDevice {
 public:
  EzoHumSensor() = default;

  void setup() override;
  void update() override;
  void dump_config() override;

  void set_humidity_sensor(sensor::Sensor *s) { humidity_sensor_ = s; }
  void set_temperature_sensor(sensor::Sensor *s) { temperature_sensor_ = s; }
  void set_dewpoint_sensor(sensor::Sensor *s) { dewpoint_sensor_ = s; }

 protected:
  bool read_line(std::string &result);
  void parse_reading(const std::string &response);

  sensor::Sensor *humidity_sensor_{nullptr};
  sensor::Sensor *temperature_sensor_{nullptr};
  sensor::Sensor *dewpoint_sensor_{nullptr};

 private:
  uint32_t start_time_{0};
  bool waiting_for_response_{false};
};

}  // namespace ezo_hum
}  // namespace esphome