#ifndef PARTICIPANTINFO_H
#define PARTICIPANTINFO_H

#include <QString>

/*!
 * \brief The ParticipantInfo class stores the participant name, their car name, and the race time for their four races.
 */
class ParticipantInfo
{
private:

    QString m_participantName;  /*!< The name of the participant */
    QString m_carName;          /*!< The name of the participant's car */
    float   m_raceTimes[4];     /*!< The race times in each lane */

public:

    //! Default onstructor.
    ParticipantInfo();

    //! Constructor for names and no race times.
    /*!
      Sets the member name and car name, with zero race times.
    */
    ParticipantInfo(QString name, QString carName);

    //! Contructor for names and race times.
    /*!
      Sets the member name, car name, and race times.
    */
    ParticipantInfo(QString name, QString carName, float raceTimes[4]);

    //! Accessor for the participant name.
    QString participantName();

    //! Accessor for the //! Accessor for the participant name. name.
    QString carName();

    //! Getter for one race time.
    //! \param idx The index of the race by lane number (0=A,1=B,2=C,3=D)
    float raceTime(int idx);

    //! Setter for one race time.
    //! \param idx The index of the race by lane number (0=A,1=B,2=C,3=D)
    //! \param time The race time to be set
    void setRaceTime(int idx, float time);
};

#endif // PARTICIPANTINFO_H
