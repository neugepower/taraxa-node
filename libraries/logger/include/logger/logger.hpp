#pragma once

#include <boost/log/sources/severity_channel_logger.hpp>
#include <string>
#include <string_view>
#include <ostream>

#include "common/types.hpp"
#include "logger/logger_config.hpp"

namespace taraxa::logger {

struct LoggerRust {
  void* logger;
  Verbosity verbosity;
  const char* channel;
};

#ifdef __cplusplus
extern "C" {

LoggerRust createLoggerRust(Verbosity verbosity, const char* channel, addr_t node_id);

void sink(LoggerRust logger, const char* msg);

#endif
#ifdef __cplusplus
}
#endif

struct Sink {
  LoggerRust logger;
  std::ostringstream stream;
  bool done = false;
  ~Sink() {
    sink(logger, stream.str().c_str());
  }
};

// Concurrent (Thread-safe) logger type
using Logger = boost::log::sources::severity_channel_logger_mt<>;

/**
 * @brief Creates thread-safe severity channel logger
 * @note To control logging in terms of where log messages are forwarded(console/file), severity filter etc..., see
 *       functions createDefaultLoggingConfig and InitLogging. Usage example:
 *
 *       // Creates logging config
 *       auto logging_config = createDefaultLoggingConfig();
 *       logging_config.verbosity = logger::Verbosity::Error;
 *       logging_config.channels["SAMPLE_CHANNEL"] = logger::Verbosity::Error;
 *
 *       // Initializes logging according to the provided config
 *       InitLogging(logging_config);
 *
 *       addr_t node_addr;
 *
 *       // Creates error logger
 *       auto logger = createLogger(logger::Verbosity::Error, "SAMPLE_CHANNEL", node_addr)
 *
 *       LOG(logger) << "sample message";
 *
 * @note see macros LOG_OBJECTS_DEFINE, LOG_OBJECTS_CREATE, LOG
 * @param verboseLevel
 * @param _channel
 * @param node_id
 * @return Logger object
 */
Logger createLogger(Verbosity verboseLevel, const std::string& channel, const addr_t& node_id);

/**
 * @brief Creates default logging config
 *
 * @return logger::Config
 */
Config createDefaultLoggingConfig();

/**
 * @brief Initializes logging according to the provided logging_config
 *
 * @param logging_config
 * @param node_id
 */
void InitLogging(Config& logging_config, const addr_t& node_id);

}  // namespace taraxa::logger

#define LOG(_logger_)                                                          \
  for (auto sink=taraxa::logger::Sink{ _logger_ }; !sink.done; sink.done=true) \
    sink.stream

#define LOG_OBJECTS_DEFINE                    \
  mutable taraxa::logger::LoggerRust log_si_; \
  mutable taraxa::logger::LoggerRust log_er_; \
  mutable taraxa::logger::LoggerRust log_wr_; \
  mutable taraxa::logger::LoggerRust log_nf_; \
  mutable taraxa::logger::LoggerRust log_dg_; \
  mutable taraxa::logger::LoggerRust log_tr_;

#define LOG_OBJECTS_DEFINE_SUB(group)                   \
  mutable taraxa::logger::LoggerRust log_si_##group##_; \
  mutable taraxa::logger::LoggerRust log_er_##group##_; \
  mutable taraxa::logger::LoggerRust log_wr_##group##_; \
  mutable taraxa::logger::LoggerRust log_nf_##group##_; \
  mutable taraxa::logger::LoggerRust log_dg_##group##_; \
  mutable taraxa::logger::LoggerRust log_tr_##group##_;

#define LOG_OBJECTS_CREATE(channel)                                                                              \
  auto __channel__ = std::string_view{ channel };                                                                \
  log_si_ = taraxa::logger::createLoggerRust(taraxa::logger::Verbosity::Silent, __channel__.data(), node_addr);  \
  log_er_ = taraxa::logger::createLoggerRust(taraxa::logger::Verbosity::Error, __channel__.data(), node_addr);   \
  log_wr_ = taraxa::logger::createLoggerRust(taraxa::logger::Verbosity::Warning, __channel__.data(), node_addr); \
  log_nf_ = taraxa::logger::createLoggerRust(taraxa::logger::Verbosity::Info, __channel__.data(), node_addr);    \
  log_tr_ = taraxa::logger::createLoggerRust(taraxa::logger::Verbosity::Trace, __channel__.data(), node_addr);   \
  log_dg_ = taraxa::logger::createLoggerRust(taraxa::logger::Verbosity::Debug, __channel__.data(), node_addr);

#define LOG_OBJECTS_CREATE_SUB(channel, group)                                                                             \
  auto __channel__ = std::string_view{ channel };                                                                          \
  log_si_##group##_ = taraxa::logger::createLoggerRust(taraxa::logger::Verbosity::Silent, __channel__.data(), node_addr);  \
  log_er_##group##_ = taraxa::logger::createLoggerRust(taraxa::logger::Verbosity::Error, __channel__.data(), node_addr);   \
  log_wr_##group##_ = taraxa::logger::createLoggerRust(taraxa::logger::Verbosity::Warning, __channel__.data(), node_addr); \
  log_nf_##group##_ = taraxa::logger::createLoggerRust(taraxa::logger::Verbosity::Info, __channel__.data(), node_addr);    \
  log_tr_##group##_ = taraxa::logger::createLoggerRust(taraxa::logger::Verbosity::Trace, __channel__.data(), node_addr);   \
  log_dg_##group##_ = taraxa::logger::createLoggerRust(taraxa::logger::Verbosity::Debug, __channel__.data(), node_addr);
