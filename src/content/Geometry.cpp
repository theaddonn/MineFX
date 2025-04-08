#pragma once
#include "../utils/Json.cpp"
#include "../utils/Vec.cpp"
#include <expected>
#include <optional>
#include <string>

struct Geometry {
    std::string name;
    std::vector<GeometryBone> bones = {};

    static std::expected<Geometry, JsonError> from_json(const json& j) {
        Geometry geometry;

        geometry.name = j.at("name").get<std::string>();
        for (const auto& bone_json : j.at("bones")) {
            std::expected<GeometryBone, JsonError> bone = GeometryBone::from_json(bone_json);

            if (!bone) {
                throw JsonError(JsonError::Type::SubError,
                                "Failed to parse GeometryBone: " + bone.error().to_string());
            }

            geometry.bones.push_back(bone.value());
        }

        return geometry;
    }

    json to_json() const {
        json j;
        j["name"] = name;
        for (const auto& bone : bones) {
            j["bones"].push_back(bone.to_json());
        }
        return j;
    }
};

struct GeometryBone {
    std::string name;
    std::optional<std::string> parent = std::nullopt;

    Vec3<float> origin   = {};
    Vec3<float> size     = {};
    Vec3<float> rotation = {};
    Vec3<float> pivot    = {};

    static std::expected<GeometryBone, JsonError> from_json(const json& j) {
        GeometryBone bone;

        bone.name = j.at("name").get<std::string>();

        if (j.contains("parent") && !j["parent"].is_null()) {
            bone.parent = j.at("parent").get<std::string>();
        }

        bone.origin   = Vec3<float>::from_json(j.at("origin"));
        bone.size     = Vec3<float>::from_json(j.at("size"));
        bone.rotation = Vec3<float>::from_json(j.at("rotation"));
        bone.pivot    = Vec3<float>::from_json(j.at("pivot"));

        return bone;
    }

    json to_json() const {
        json json;

        json["name"] = name;
        if (parent.has_value()) {
            json["parent"] = parent.value();
        }
        json["origin"]   = origin.to_json();
        json["size"]     = size.to_json();
        json["rotation"] = rotation.to_json();
        json["pivot"]    = pivot.to_json();

        return json;
    }
};
