#ifndef PARTICIPANTINFO_H
#define PARTICIPANTINFO_H

#include <QString>

class ParticipantInfo
{
private:
    QString m_participantName;
    QString m_carName;
    float   m_raceTimes[4];

public:
    ParticipantInfo();
    ParticipantInfo(QString name, QString carName);
    ParticipantInfo(QString name, QString carName, float raceTimes[4]);

    QString participantName();
    QString carName();
    float raceTime(int idx);
    void setRaceTime(int idx, float time);
};

#endif // PARTICIPANTINFO_H
