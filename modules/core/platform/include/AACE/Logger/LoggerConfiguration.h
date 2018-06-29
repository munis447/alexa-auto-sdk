/*
 * Copyright 2017-2018 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *     http://aws.amazon.com/apache2.0/
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#ifndef AACE_LOGGER_LOGGER_CONFIGURATION_H
#define AACE_LOGGER_LOGGER_CONFIGURATION_H

#include <utility>

#include "AACE/Core/EngineConfiguration.h"
#include "LoggerEngineInterfaces.h"

/** @file */

namespace aace {
namespace logger {
namespace config {

class SinkConfiguration;
class RuleConfiguration;

/**
 * @code{.json}
 * {
 *   "aace.logger":
 *   {
 *      "sinks": [<Sink>],
 *      "rules": [{"sink": "<SINK_ID>", "rule": <Rule>}]
 *   }
 * }
 *
 * <Sink>: {
 *   "id": "<SINK_ID>"
 *   "type": "<SINK_TYPE>",
 *   "config": {
 *     <CONFIG_DATA>
 *   },
 *   "rules": [<RuleConfiguration>]
 * }
 *
 * <Rule>: {
 *   "level": "<LOG_LEVEL>",
 *   "source": "<SOURCE_FILTER>",
 *   "tag": "<TAG_FILTER>",
 *   "message": "<MESSAGE_FILTER>"
 * }
 * @endcode
 */

class LoggerConfiguration {
public:
     /**
      * Specifies the severity level of a log message
      * @sa @c aace::logger::LoggerEngineInterface::Level
      */
    using Level = aace::logger::LoggerEngineInterface::Level;

    /**
     * Factory method used to programmatically generate logger configuration data for a console sink.
     * The data generated by this method is equivalent to providing the following JSON values
     * in a configuration file:
     *
     * @code{.json}
     * {
     *   "aace.logger":
     *   {
     *     "sinks": [{
     *       "id": "<SINK_ID>",
     *       "type": "aace.logger.sink.console",
     *       "rules": [{
     *         "level": <LOG_LEVEL>
     *       }]
     *     }
     *   }
     * }
     * @endcode
     *
     * @param [in] id The id of sink object
     * @param [in] level The log level to be used to filter logs to this sink
     */
    static std::shared_ptr<aace::core::config::EngineConfiguration> createConsoleSinkConfig( const std::string& id, Level level );

    /**
     * Factory method used to programmatically generate logger configuration data for a syslog sink.
     * The data generated by this method is equivalent to providing the following JSON values
     * in a configuration file:
     *
     * @code{.json}
     * {
     *   "aace.logger":
     *   {
     *     "sinks": [{
     *       "id": "<SINK_ID>",
     *       "type": "aace.logger.sink.syslog",
     *       "rules": [{
     *         "level": <LOG_LEVEL>
     *       }]
     *     }
     *   }
     * }
     * @endcode
     *
     * @param [in] id The id of sink object
     * @param [in] level The log level to be used to filter logs to this sink
     */
    static std::shared_ptr<aace::core::config::EngineConfiguration> createSyslogSinkConfig( const std::string& id, Level level );

    /**
     * Factory method used to programmatically generate logger configuration data for a file sink.
     * The data generated by this method is equivalent to providing the following JSON values
     * in a configuration file:
     *
     * @code{.json}
     * {
     *   "aace.logger":
     *   {
     *     "sinks": [{
     *       "id": "<SINK_ID>",
     *       "type": "aace.logger.sink.file",
     *       "config": {
     *         "path": "<PATH>",
     *         "prefix": "<PREFIX>",
     *         "maxSize": <MAX_SIZE>,
     *         "maxFiles": <MAX_FILES>,
     *         "append": <APPEND>
     *       }
     *       "rules": [{
     *         "level": <LOG_LEVEL>
     *       }]
     *     }
     *   }
     * }
     * @endcode
     *
     * @param [in] id The id of sink object
     * @param [in] level The log level to be used to filter logs to this sink
     * @param [in] path The parent path where the log files will be written (must exist)
     * @param [in] prefix The prefix name given to the log file
     * @param [in] maxSize The maximum log file size in bytes
     * @param [in] maxFiles The maximum number of log files to rotate
     * @param [in] append @c true If the logs should be appended to the existing file, @c false if the file should be overwritten
     */
    static std::shared_ptr<aace::core::config::EngineConfiguration> createFileSinkConfig( const std::string& id, Level level, const std::string& path, const std::string& prefix = "aace", uint32_t maxSize = 5242880, uint32_t maxFiles = 3, bool append = true );

    /**
     * Factory method used to programmatically generate configuration data for a logger rule.
     * The data generated by this method is equivalent to providing the following JSON values
     * in a configuration file:
     *
     * @code{.json}
     * {
     *   "aace.logger":
     *   {
     *     "rules": [{
     *       "sink": "<SINK_ID>",
     *       "rule": {
     *         "level": <LOG_LEVEL>,
     *         "source": "<SOURCE_FILTER>",
     *         "tag": "<TAG_FILTER>",
     *         "message": "<MESSAGE_FILTER>"
     *       }
     *     }
     *   }
     * }
     * @endcode
     *
     * @param [in] sink The id of sink object to which this rule is applied
     * @param [in] level The log level to be used as a filter for this rule
     * @param [in] sourceFilter The source regex to be used as a filter for this rule
     * @param [in] tagFilter The tag regex to be used as a filter for this rule
     * @param [in] messageFilter The message regex to be used as a filter for this rule
     */
    static std::shared_ptr<aace::core::config::EngineConfiguration> createLoggerRuleConfig( const std::string& sink, Level level, const std::string& sourceFilter = "", const std::string& tagFilter = "", const std::string& messageFilter = "" );
};

} // aace::logger::config
} // aace::logger
} // aace

#endif // AACE_LOGGER_LOGGER_CONFIGURATION_H
