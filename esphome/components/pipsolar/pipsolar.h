#pragma once

#include "esphome/components/binary_sensor/binary_sensor.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/switch/switch.h"
#include "esphome/components/text_sensor/text_sensor.h"
#include "esphome/components/uart/uart.h"
#include "esphome/core/automation.h"
#include "esphome/core/component.h"

namespace esphome {
namespace pipsolar {

enum ENUMPollingCommand {
  POLLING_P007PIRI = 0,
  POLLING_P005GS = 1,
  POLLING_QMOD = 2,
  POLLING_QFLAG = 3,
  POLLING_QPIWS = 4,
  POLLING_QT = 5,
  POLLING_QMN = 6,
};
struct PollingCommand {
  uint8_t *command;
  uint8_t length = 0;
  uint8_t errors;
  ENUMPollingCommand identifier;
};

#define PIPSOLAR_VALUED_ENTITY_(type, name, polling_command, value_type) \
 protected: \
  value_type value_##name##_; \
  PIPSOLAR_ENTITY_(type, name, polling_command)

#define PIPSOLAR_ENTITY_(type, name, polling_command) \
 protected: \
  type *name##_{}; /* NOLINT */ \
\
 public: \
  void set_##name(type *name) { /* NOLINT */ \
    this->name##_ = name; \
    this->add_polling_command_("^"#polling_command, POLLING_##polling_command); \
  }

#define PIPSOLAR_SENSOR(name, polling_command, value_type) \
  PIPSOLAR_VALUED_ENTITY_(sensor::Sensor, name, polling_command, value_type)
#define PIPSOLAR_SWITCH(name, polling_command) PIPSOLAR_ENTITY_(switch_::Switch, name, polling_command)
#define PIPSOLAR_BINARY_SENSOR(name, polling_command, value_type) \
  PIPSOLAR_VALUED_ENTITY_(binary_sensor::BinarySensor, name, polling_command, value_type)
#define PIPSOLAR_VALUED_TEXT_SENSOR(name, polling_command, value_type) \
  PIPSOLAR_VALUED_ENTITY_(text_sensor::TextSensor, name, polling_command, value_type)
#define PIPSOLAR_TEXT_SENSOR(name, polling_command) PIPSOLAR_ENTITY_(text_sensor::TextSensor, name, polling_command)

class Pipsolar : public uart::UARTDevice, public PollingComponent {
  // P005GS values
  PIPSOLAR_SENSOR(grid_voltage, P005GS, float)
  PIPSOLAR_SENSOR(grid_frequency, P005GS, float)
  PIPSOLAR_SENSOR(ac_output_voltage, P005GS, float)
  PIPSOLAR_SENSOR(ac_output_frequency, P005GS, float)
  PIPSOLAR_SENSOR(ac_output_apparent_power, P005GS, int)
  PIPSOLAR_SENSOR(ac_output_active_power, P005GS, int)
  PIPSOLAR_SENSOR(output_load_percent, P005GS, int)
  PIPSOLAR_SENSOR(bus_voltage, P005GS, int)
  PIPSOLAR_SENSOR(battery_voltage, P005GS, float)
  PIPSOLAR_SENSOR(battery_charging_current, P005GS, int)
  PIPSOLAR_SENSOR(battery_capacity_percent, P005GS, int)
  PIPSOLAR_SENSOR(inverter_heat_sink_temperature, P005GS, int)
  PIPSOLAR_SENSOR(pv_input_current_for_battery, P005GS, float)
  PIPSOLAR_SENSOR(pv_input_voltage, P005GS, float)
  PIPSOLAR_SENSOR(battery_voltage_scc, P005GS, float)
  PIPSOLAR_SENSOR(battery_discharge_current, P005GS, int)
  PIPSOLAR_BINARY_SENSOR(add_sbu_priority_version, P005GS, int)
  PIPSOLAR_BINARY_SENSOR(configuration_status, P005GS, int)
  PIPSOLAR_BINARY_SENSOR(scc_firmware_version, P005GS, int)
  PIPSOLAR_BINARY_SENSOR(load_status, P005GS, int)
  PIPSOLAR_BINARY_SENSOR(battery_voltage_to_steady_while_charging, P005GS, int)
  PIPSOLAR_BINARY_SENSOR(charging_status, P005GS, int)
  PIPSOLAR_BINARY_SENSOR(scc_charging_status, P005GS, int)
  PIPSOLAR_BINARY_SENSOR(ac_charging_status, P005GS, int)
  PIPSOLAR_SENSOR(battery_voltage_offset_for_fans_on, P005GS, int)  //.1 scale
  PIPSOLAR_SENSOR(eeprom_version, P005GS, int)
  PIPSOLAR_SENSOR(pv_charging_power, P005GS, int)
  PIPSOLAR_BINARY_SENSOR(charging_to_floating_mode, P005GS, int)
  PIPSOLAR_BINARY_SENSOR(switch_on, P005GS, int)
  PIPSOLAR_BINARY_SENSOR(dustproof_installed, P005GS, int)

  // P007PIRI values
  PIPSOLAR_SENSOR(grid_rating_voltage, P007PIRI, float)
  PIPSOLAR_SENSOR(grid_rating_current, P007PIRI, float)
  PIPSOLAR_SENSOR(ac_output_rating_voltage, P007PIRI, float)
  PIPSOLAR_SENSOR(ac_output_rating_frequency, P007PIRI, float)
  PIPSOLAR_SENSOR(ac_output_rating_current, P007PIRI, float)
  PIPSOLAR_SENSOR(ac_output_rating_apparent_power, P007PIRI, int)
  PIPSOLAR_SENSOR(ac_output_rating_active_power, P007PIRI, int)
  PIPSOLAR_SENSOR(battery_rating_voltage, P007PIRI, float)
  PIPSOLAR_SENSOR(battery_recharge_voltage, P007PIRI, float)
  PIPSOLAR_SENSOR(battery_under_voltage, P007PIRI, float)
  PIPSOLAR_SENSOR(battery_bulk_voltage, P007PIRI, float)
  PIPSOLAR_SENSOR(battery_float_voltage, P007PIRI, float)
  PIPSOLAR_SENSOR(battery_type, P007PIRI, int)
  PIPSOLAR_SENSOR(current_max_ac_charging_current, P007PIRI, int)
  PIPSOLAR_SENSOR(current_max_charging_current, P007PIRI, int)
  PIPSOLAR_SENSOR(input_voltage_range, P007PIRI, int)
  PIPSOLAR_SENSOR(output_source_priority, P007PIRI, int)
  PIPSOLAR_SENSOR(charger_source_priority, P007PIRI, int)
  PIPSOLAR_SENSOR(parallel_max_num, P007PIRI, int)
  PIPSOLAR_SENSOR(machine_type, P007PIRI, int)
  PIPSOLAR_SENSOR(topology, P007PIRI, int)
  PIPSOLAR_SENSOR(output_mode, P007PIRI, int)
  PIPSOLAR_SENSOR(battery_redischarge_voltage, P007PIRI, float)
  PIPSOLAR_SENSOR(pv_ok_condition_for_parallel, P007PIRI, int)
  PIPSOLAR_SENSOR(pv_power_balance, P007PIRI, int)

  // QMOD values
  PIPSOLAR_VALUED_TEXT_SENSOR(device_mode, QMOD, char)

  // QFLAG values
  PIPSOLAR_BINARY_SENSOR(silence_buzzer_open_buzzer, QFLAG, int)
  PIPSOLAR_BINARY_SENSOR(overload_bypass_function, QFLAG, int)
  PIPSOLAR_BINARY_SENSOR(lcd_escape_to_default, QFLAG, int)
  PIPSOLAR_BINARY_SENSOR(overload_restart_function, QFLAG, int)
  PIPSOLAR_BINARY_SENSOR(over_temperature_restart_function, QFLAG, int)
  PIPSOLAR_BINARY_SENSOR(backlight_on, QFLAG, int)
  PIPSOLAR_BINARY_SENSOR(alarm_on_when_primary_source_interrupt, QFLAG, int)
  PIPSOLAR_BINARY_SENSOR(fault_code_record, QFLAG, int)
  PIPSOLAR_BINARY_SENSOR(power_saving, QFLAG, int)

  // QPIWS values
  PIPSOLAR_BINARY_SENSOR(warnings_present, QPIWS, bool)
  PIPSOLAR_BINARY_SENSOR(faults_present, QPIWS, bool)
  PIPSOLAR_BINARY_SENSOR(warning_power_loss, QPIWS, bool)
  PIPSOLAR_BINARY_SENSOR(fault_inverter_fault, QPIWS, bool)
  PIPSOLAR_BINARY_SENSOR(fault_bus_over, QPIWS, bool)
  PIPSOLAR_BINARY_SENSOR(fault_bus_under, QPIWS, bool)
  PIPSOLAR_BINARY_SENSOR(fault_bus_soft_fail, QPIWS, bool)
  PIPSOLAR_BINARY_SENSOR(warning_line_fail, QPIWS, bool)
  PIPSOLAR_BINARY_SENSOR(fault_opvshort, QPIWS, bool)
  PIPSOLAR_BINARY_SENSOR(fault_inverter_voltage_too_low, QPIWS, bool)
  PIPSOLAR_BINARY_SENSOR(fault_inverter_voltage_too_high, QPIWS, bool)
  PIPSOLAR_BINARY_SENSOR(warning_over_temperature, QPIWS, bool)
  PIPSOLAR_BINARY_SENSOR(warning_fan_lock, QPIWS, bool)
  PIPSOLAR_BINARY_SENSOR(warning_battery_voltage_high, QPIWS, bool)
  PIPSOLAR_BINARY_SENSOR(warning_battery_low_alarm, QPIWS, bool)
  PIPSOLAR_BINARY_SENSOR(warning_battery_under_shutdown, QPIWS, bool)
  PIPSOLAR_BINARY_SENSOR(warning_battery_derating, QPIWS, bool)
  PIPSOLAR_BINARY_SENSOR(warning_over_load, QPIWS, bool)
  PIPSOLAR_BINARY_SENSOR(warning_eeprom_failed, QPIWS, bool)
  PIPSOLAR_BINARY_SENSOR(fault_inverter_over_current, QPIWS, bool)
  PIPSOLAR_BINARY_SENSOR(fault_inverter_soft_failed, QPIWS, bool)
  PIPSOLAR_BINARY_SENSOR(fault_self_test_failed, QPIWS, bool)
  PIPSOLAR_BINARY_SENSOR(fault_op_dc_voltage_over, QPIWS, bool)
  PIPSOLAR_BINARY_SENSOR(fault_battery_open, QPIWS, bool)
  PIPSOLAR_BINARY_SENSOR(fault_current_sensor_failed, QPIWS, bool)
  PIPSOLAR_BINARY_SENSOR(fault_battery_short, QPIWS, bool)
  PIPSOLAR_BINARY_SENSOR(warning_power_limit, QPIWS, bool)
  PIPSOLAR_BINARY_SENSOR(warning_pv_voltage_high, QPIWS, bool)
  PIPSOLAR_BINARY_SENSOR(fault_mppt_overload, QPIWS, bool)
  PIPSOLAR_BINARY_SENSOR(warning_mppt_overload, QPIWS, bool)
  PIPSOLAR_BINARY_SENSOR(warning_battery_too_low_to_charge, QPIWS, bool)
  PIPSOLAR_BINARY_SENSOR(fault_dc_dc_over_current, QPIWS, bool)
  PIPSOLAR_BINARY_SENSOR(fault_code, QPIWS, int)
  PIPSOLAR_BINARY_SENSOR(warnung_low_pv_energy, QPIWS, bool)
  PIPSOLAR_BINARY_SENSOR(warning_high_ac_input_during_bus_soft_start, QPIWS, bool)
  PIPSOLAR_BINARY_SENSOR(warning_battery_equalization, QPIWS, bool)

  PIPSOLAR_TEXT_SENSOR(last_qpigs, P005GS)
  PIPSOLAR_TEXT_SENSOR(last_qpiri, P007PIRI)
  PIPSOLAR_TEXT_SENSOR(last_qmod, QMOD)
  PIPSOLAR_TEXT_SENSOR(last_qflag, QFLAG)
  PIPSOLAR_TEXT_SENSOR(last_qpiws, QPIWS)
  PIPSOLAR_TEXT_SENSOR(last_qt, QT)
  PIPSOLAR_TEXT_SENSOR(last_qmn, QMN)

  PIPSOLAR_SWITCH(output_source_priority_utility_switch, P007PIRI)
  PIPSOLAR_SWITCH(output_source_priority_solar_switch, P007PIRI)
  PIPSOLAR_SWITCH(output_source_priority_battery_switch, P007PIRI)
  PIPSOLAR_SWITCH(input_voltage_range_switch, P007PIRI)
  PIPSOLAR_SWITCH(pv_ok_condition_for_parallel_switch, P007PIRI)
  PIPSOLAR_SWITCH(pv_power_balance_switch, P007PIRI)

  void switch_command(const std::string &command);
  void setup() override;
  void loop() override;
  void dump_config() override;
  void update() override;

 protected:
  static const size_t PIPSOLAR_READ_BUFFER_LENGTH = 150;  // maximum supported answer length
  static const size_t COMMAND_QUEUE_LENGTH = 10;
  static const size_t COMMAND_TIMEOUT = 5000;
  uint32_t last_poll_ = 0;
  void add_polling_command_(const char *command, ENUMPollingCommand polling_command);
  void empty_uart_buffer_();
  uint8_t check_incoming_crc_();
  uint8_t check_incoming_length_(uint8_t length);
  uint16_t cal_crc_half_(uint8_t *msg, uint8_t len);
  uint8_t send_next_command_();
  void send_next_poll_();
  void queue_command_(const char *command, uint8_t length);
  std::string command_queue_[COMMAND_QUEUE_LENGTH];
  uint8_t command_queue_position_ = 0;
  uint8_t read_buffer_[PIPSOLAR_READ_BUFFER_LENGTH];
  size_t read_pos_{0};

  uint32_t command_start_millis_ = 0;
  uint8_t state_;
  enum State {
    STATE_IDLE = 0,
    STATE_POLL = 1,
    STATE_COMMAND = 2,
    STATE_POLL_COMPLETE = 3,
    STATE_COMMAND_COMPLETE = 4,
    STATE_POLL_CHECKED = 5,
    STATE_POLL_DECODED = 6,
  };

  uint8_t last_polling_command_ = 0;
  PollingCommand used_polling_commands_[15];
};

}  // namespace pipsolar
}  // namespace esphome
