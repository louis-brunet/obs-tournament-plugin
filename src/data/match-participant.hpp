#pragma once

#include <memory>
#include <obs-data.h>
#include <string>

class MatchParticipant {
public:
    enum Type {
        Unknown = -1,
        Player = 0,
        FromMatch,
    };

    static std::shared_ptr<MatchParticipant> loadStatic(obs_data_t *data);

    MatchParticipant();
    MatchParticipant(MatchParticipant &&) = default;
    MatchParticipant(const MatchParticipant &) = default;
    MatchParticipant &operator=(MatchParticipant &&) = default;
    MatchParticipant &operator=(const MatchParticipant &) = default;
    ~MatchParticipant();

    virtual std::string displayName() const = 0;
    virtual void load(obs_data_t *data);
    virtual void save(obs_data_t *data) const;

private:
    Type _type = Type::Unknown;
};
//
// MatchParticipant::MatchParticipant() {
// }
//
// MatchParticipant::~MatchParticipant() {
// }
