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
    int     m_carNumber;        /*!< The name of the participant's car */
    float   m_raceTimes[4];     /*!< The race times in each lane */

private:

    //! Default onstructor.
    ParticipantInfo();

    //! Constructor for names and no race times.


public:
    //! Contructor for names and race times.
    /*!
      Sets the member name and car name, with zero race times.
    */
    ParticipantInfo(QString name, QString carName, int carNumber);


    /*!
      Sets the member name, car name, and race times.
    */
    ParticipantInfo(QString name, QString carName, int carNumber, float raceTimes[4]);

    //! Accessor for the participant name.
    QString participantName();

    //! Accessor for the //! Accessor for the participant name. name.
    QString carName();

    int carNumber() { return m_carNumber; }

    //! Getter for one race time.
    //! \param idx The index of the race by lane number (0=A,1=B,2=C,3=D)
    float raceTime(int idx);

    //! Setter for one race time.
    //! \param idx The index of the race by lane number (0=A,1=B,2=C,3=D)
    //! \param time The race time to be set
    void setRaceTime(int idx, float time);

    float averageRaceTime();
};

#endif // PARTICIPANTINFO_H
