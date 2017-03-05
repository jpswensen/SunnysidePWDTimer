#include "participantinfo.h"

ParticipantInfo::ParticipantInfo()
    : m_participantName(""), m_carName("")
{
    for (int i = 0 ; i < 4 ; i++)
    {
        m_raceTimes[i] = 0.0;
    }
}

ParticipantInfo::ParticipantInfo(QString name, QString carName)
{
    m_participantName = name;
    m_carName = carName;

    for (int i = 0 ; i < 4 ; i++)
    {
        m_raceTimes[i] = 0.0;
    }
}

ParticipantInfo::ParticipantInfo(QString name, QString carName, float raceTimes[4])
{
    m_participantName = name;
    m_carName = carName;

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
