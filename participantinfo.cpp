#include "participantinfo.h"

ParticipantInfo::ParticipantInfo()
    : m_participantName(""), m_carName("")
{
    for (int i = 0 ; i < 4 ; i++)
    {
        m_raceTimes[i] = 0.0;
    }
}

ParticipantInfo::ParticipantInfo(QString name, QString carName, int carNumber)
{
    m_participantName = name;
    m_carName = carName;
    m_carNumber = carNumber;

    for (int i = 0 ; i < 4 ; i++)
    {
        m_raceTimes[i] = 0.0;
    }
}

ParticipantInfo::ParticipantInfo(QString name, QString carName, int carNumber, float raceTimes[4])
{
    m_participantName = name;
    m_carName = carName;
    m_carNumber = carNumber;

    for (int i = 0 ; i < 4 ; i++)
    {
        m_raceTimes[i] = raceTimes[i];
    }
}

QString ParticipantInfo::participantName()
{
    return m_participantName;
}

QString ParticipantInfo::carName()
{
    return m_carName;
}

float ParticipantInfo::raceTime(int idx)
{
    return m_raceTimes[idx];
}

void ParticipantInfo::setRaceTime(int idx, float time)
{
    m_raceTimes[idx] = time;
}

float ParticipantInfo::averageRaceTime()
{
    return (m_raceTimes[0]+m_raceTimes[1]+m_raceTimes[2]+m_raceTimes[3])/4.0;
}
