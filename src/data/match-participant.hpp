#pragma once

#include <memory>
#include <obs-data.h>
#include <string>

class MatchReferenceRemap;
class MatchReference;

// class ValidateConfigurationResult {
//     bool isValid;
// }

class MatchParticipant {
public:
    enum Type {
        Unknown = -1,
        Player = 0,
        FromMatch,
    };
    enum ValidateConfigurationResult {
        Valid,
        InvalidUnknownParticipant,
        InvalidCircularDependency,
        InvalidPlayerVersusSelf,
    };

    static std::shared_ptr<MatchParticipant> loadStatic(obs_data_t *data);

    MatchParticipant(Type type = Type::Unknown);
    MatchParticipant(MatchParticipant &&) = default;
    MatchParticipant(const MatchParticipant &) = default;
    MatchParticipant &operator=(MatchParticipant &&) = default;
    MatchParticipant &operator=(const MatchParticipant &) = default;
    virtual ~MatchParticipant();

    virtual std::shared_ptr<MatchParticipant> duplicate() const = 0;
    virtual std::string displayName() const = 0;
    // virtual bool isPlayerKnown();
    virtual ValidateConfigurationResult validateConfiguration(const MatchReference &matchContext) const = 0;

    virtual void load(obs_data_t *data);
    virtual void save(obs_data_t *data) const;

    virtual void applyRemap(const MatchReferenceRemap *remap, const MatchReference &matchContext);

    Type type() const;

private:
    Type _type = Type::Unknown;
};
//
// MatchParticipant::MatchParticipant() {
// }
//
// MatchParticipant::~MatchParticipant() {
// }
