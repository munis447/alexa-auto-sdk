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

#ifndef AACE_ENGINE_LOGGER_LOGGER_ENGINE_SERVICE_H
#define AACE_ENGINE_LOGGER_LOGGER_ENGINE_SERVICE_H

#include "AACE/Engine/Core/EngineService.h"
#include "EngineLogger.h"
#include "LoggerEngineImpl.h"

namespace aace {
namespace engine {
namespace logger {

class LoggerEngineService : public aace::engine::core::EngineService {
public:
    DESCRIBE("aace.logger",VERSION("1.0"))

private:
    LoggerEngineService( const aace::engine::core::ServiceDescription& description );

public:
    virtual ~LoggerEngineService() = default;

protected:
    bool configure( const std::vector<std::shared_ptr<std::istream>>& configuration ) override;
    bool registerPlatformInterface( std::shared_ptr<aace::core::PlatformInterface> platformInterface ) override;

private:
    bool configure( std::shared_ptr<std::istream> configuration );
    
    std::shared_ptr<aace::engine::logger::sink::Sink> createSink( const rapidjson::Value& config );
    std::shared_ptr<aace::engine::logger::sink::Rule> createRule( const rapidjson::Value& config );

    // platform interface registration
    template <class T>
    bool registerPlatformInterfaceType( std::shared_ptr<aace::core::PlatformInterface> platformInterface ) {
        std::shared_ptr<T> typedPlatformInterface = std::dynamic_pointer_cast<T>( platformInterface );
        return typedPlatformInterface != nullptr ? registerPlatformInterfaceType( typedPlatformInterface ) : false;
    }
    
    bool registerPlatformInterfaceType( std::shared_ptr<aace::logger::Logger> logger );

private:
    std::shared_ptr<aace::engine::logger::LoggerEngineImpl> m_loggerEngineImpl;
};

} // aace::engine::logger
} // aace::engine
} // aace

#endif // AACE_ENGINE_LOGGER_LOGGER_ENGINE_SERVICE_H
