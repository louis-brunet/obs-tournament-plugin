#pragma once

#include <memory>
#include <obs-data.h>
#include <string>

class MatchReferenceRemap;

class MatchParticipant {
public:
    enum Type {
        Unknown = -1,
        Player = 0,
        FromMatch,
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
    virtual void load(obs_data_t *data);
    virtual void save(obs_data_t *data) const;

    virtual void applyRemap(const MatchReferenceRemap *remap);

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
