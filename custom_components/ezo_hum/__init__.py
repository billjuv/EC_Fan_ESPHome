import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import i2c, sensor
from esphome.const import (
    CONF_ID,
    UNIT_PERCENT,
    UNIT_CELSIUS,
    ICON_WATER_PERCENT,
    ICON_THERMOMETER,
)

DEPENDENCIES = ["i2c"]

ezo_hum_ns = cg.esphome_ns.namespace("ezo_hum")
EzoHumSensor = ezo_hum_ns.class_("EzoHumSensor", cg.PollingComponent, i2c.I2CDevice)

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(EzoHumSensor),
        cv.Optional("address", default=0x6F): cv.i2c_address,
        cv.Optional("update_interval", default="10s"): cv.update_interval,
        cv.Required("humidity"): sensor.sensor_schema(
            unit_of_measurement=UNIT_PERCENT,
            icon=ICON_WATER_PERCENT,
            accuracy_decimals=2,
        ),
        cv.Required("temperature"): sensor.sensor_schema(
            unit_of_measurement=UNIT_CELSIUS,
            icon=ICON_THERMOMETER,
            accuracy_decimals=2,
        ),
        cv.Optional("dew_point"): sensor.sensor_schema(
            unit_of_measurement=UNIT_CELSIUS,
            icon=ICON_THERMOMETER,
            accuracy_decimals=2,
        ),
    }
).extend(cv.polling_component_schema("10s")).extend(i2c.i2c_device_schema(0x6F))


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await i2c.register_i2c_device(var, config)

    # Link humidity sensor
    sens = await sensor.new_sensor(config["humidity"])
    cg.add(var.set_humidity_sensor(sens))

    # Link temperature sensor
    sens = await sensor.new_sensor(config["temperature"])
    cg.add(var.set_temperature_sensor(sens))

    # Link dew point sensor (optional)
    if "dew_point" in config:
        sens = await sensor.new_sensor(config["dew_point"])
        cg.add(var.set_dewpoint_sensor(sens))