#pragma once

#include "src/data/match-participant.hpp"
#include "src/data/match-reference.hpp"
#include "src/data/player-reference.hpp"
#include <QWidget>
#include <QComboBox>
#include <memory>

struct PlayerComboBoxData {
    enum Type {
        Unknown = -1,
        Player,
        WinnerOf,
        LoserOf,
    };

    Type type = Type::Unknown;
    union {
        void *empty = nullptr;
        PlayerReference playerReference;
    };

    PlayerComboBoxData(Type type = Type::Unknown);
    PlayerComboBoxData(PlayerReference playerReference);
    ~PlayerComboBoxData();
};

struct FromMatchComboBoxData {
    // enum Type { Unknown, Match };
    //
    // Type type;
    // union {
    // 	void *empty = nullptr;
    MatchReference fromMatchReference = MatchReference();
    // };

    // FromMatchComboBoxData(Type type = Type::Unknown);
    // FromMatchComboBoxData();
    FromMatchComboBoxData(MatchReference fromMatchReference = MatchReference());
    ~FromMatchComboBoxData();
};

class MatchParticipantInput : public QWidget {
    Q_OBJECT;

public:
    MatchParticipantInput();
    // MatchParticipantInput(std::shared_ptr<MatchParticipant> existingParticipant);
    ~MatchParticipantInput();

    void setPlayers(const std::vector<PlayerReference> &players);
    void setMatches(const std::vector<MatchReference> &matches);
    void setParticipant(const std::shared_ptr<MatchParticipant> participant);

signals:
    void participantChanged(std::shared_ptr<MatchParticipant> newParticipant);

private:
    QComboBox *playerComboBox;
    QComboBox *fromMatchComboBox;
    std::shared_ptr<MatchParticipant> toMatchParticipant() const;
    // std::shared_ptr<MatchParticipant> participantOnReset;
};
