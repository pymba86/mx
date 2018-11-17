#include <mutex>
#include <unordered_map>
#include <memory>
#include "generator.hpp"

namespace mx {
    namespace generator_factory {

        namespace {
            std::mutex g_generator_mutex;
            std::unordered_map<std::string, std::shared_ptr<mx::generator>> g_generators;

        }

        std::shared_ptr<generator> create(const std::string& realm) {
            std::lock_guard<std::mutex> lock(g_generator_mutex);
            auto itr = g_generators.find(realm);
            if (itr == g_generators.end()) {
                auto gen = std::make_shared<generator>();
                g_generators[realm] = gen;
                return gen;
            }

            return itr->second;
        }
    }
}

