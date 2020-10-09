/*
 * Copyright 2017-2020 Amazon.com, Inc. or its affiliates. All Rights Reserved.
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

/*********************************************************
**********************************************************
**********************************************************

THIS FILE IS AUTOGENERATED. DO NOT EDIT

**********************************************************
**********************************************************
*********************************************************/

#ifndef EXTERNALMEDIAADAPTER_PLAYERERRORMESSAGE_H
#define EXTERNALMEDIAADAPTER_PLAYERERRORMESSAGE_H

#include <string>
#include <vector>

#include <AACE/Engine/Utils/UUID/UUID.h>
#include <nlohmann/json.hpp>

namespace aasb {
namespace message {
namespace alexa {
namespace externalMediaAdapter {

//Class Definition
struct PlayerErrorMessage {
    struct Header {
        struct MessageDescription {
            static const std::string& topic() {
                static std::string topic = "ExternalMediaAdapter";
                return topic;
            }
            static const std::string& action() {
                static std::string action = "PlayerError";
                return action;
            }
        };
        static const std::string& version() {
            static std::string version = "3.0";
            return version;
        }
        static const std::string& messageType() {
            static std::string messageType = "Publish";
            return messageType;
        }
        std::string id = aace::engine::utils::uuid::generateUUID();
        MessageDescription messageDescription;
    };
    struct Payload {
        std::string localPlayerId;
        std::string errorName;
        int code;
        std::string description;
        bool fatal;
    };
    static const std::string& topic() {
        static std::string topic = "ExternalMediaAdapter";
        return topic;
    }
    static const std::string& action() {
        static std::string action = "PlayerError";
        return action;
    }
    static const std::string& version() {
        static std::string version = "3.0";
        return version;
    }
    static const std::string& messageType() {
        static std::string messageType = "Publish";
        return messageType;
    }
    std::string toString() const;
    Header header;
    Payload payload;
};

//JSON Serialization
inline void to_json(nlohmann::json& j, const PlayerErrorMessage::Payload& c) {
    j = nlohmann::json{
        {"localPlayerId", c.localPlayerId},
        {"errorName", c.errorName},
        {"code", c.code},
        {"description", c.description},
        {"fatal", c.fatal},
    };
}
inline void from_json(const nlohmann::json& j, PlayerErrorMessage::Payload& c) {
    j.at("localPlayerId").get_to(c.localPlayerId);
    j.at("errorName").get_to(c.errorName);
    j.at("code").get_to(c.code);
    j.at("description").get_to(c.description);
    j.at("fatal").get_to(c.fatal);
}

inline void to_json(nlohmann::json& j, const PlayerErrorMessage::Header::MessageDescription& c) {
    j = nlohmann::json{
        {"topic", c.topic()},
        {"action", c.action()},
    };
}
inline void from_json(const nlohmann::json& j, PlayerErrorMessage::Header::MessageDescription& c) {
}

inline void to_json(nlohmann::json& j, const PlayerErrorMessage::Header& c) {
    j = nlohmann::json{
        {"version", c.version()},
        {"messageType", c.messageType()},
        {"id", c.id},
        {"messageDescription", c.messageDescription},
    };
}
inline void from_json(const nlohmann::json& j, PlayerErrorMessage::Header& c) {
    j.at("id").get_to(c.id);
    j.at("messageDescription").get_to(c.messageDescription);
}

inline void to_json(nlohmann::json& j, const PlayerErrorMessage& c) {
    j = nlohmann::json{
        {"header", c.header},
        {"payload", c.payload},
    };
}
inline void from_json(const nlohmann::json& j, PlayerErrorMessage& c) {
    j.at("header").get_to(c.header);
    j.at("payload").get_to(c.payload);
}

inline std::string PlayerErrorMessage::toString() const {
    nlohmann::json j = *this;
    return j.dump(3);
}

}  // namespace externalMediaAdapter
}  // namespace alexa
}  // namespace message
}  // namespace aasb

#endif  // EXTERNALMEDIAADAPTER_PLAYERERRORMESSAGE_H