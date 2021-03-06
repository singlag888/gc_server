#pragma once

#include <sys/timeb.h>
#include "perinclude.h"
#include "Singleton.h"

struct GameTimerCmp;

class GameTimer
{
	friend struct GameTimerCmp;
public:
	GameTimer(float delay);

	virtual ~GameTimer();

	bool check_time();

protected:
	virtual void on_time(float delta) {}

protected:
	long long start_;
	long long delay_;
};

struct GameTimerCmp
{
	bool operator()(const GameTimer* _Left, const GameTimer* _Right) const
	{
		return (_Left->delay_ > _Right->delay_);
	}
};


/**********************************************************************************************//**
 * \class	GameTimeManager
 *
 * \brief	A game time.
 **************************************************************************************************/

class GameTimeManager : public TSingleton < GameTimeManager >
{
public:

	/**********************************************************************************************//**
	 * \brief	Default constructor.
	 **************************************************************************************************/

	GameTimeManager();

	/**********************************************************************************************//**
	 * \brief	Destructor.
	 **************************************************************************************************/

	~GameTimeManager();

	/**********************************************************************************************//**
	 * \brief	计算当前时间.
	 *
	 * \return	A reference to a GameTime.
	 **************************************************************************************************/

	GameTimeManager& now();

	/**********************************************************************************************//**
	 * \brief	Gets second time.
	 *
	 * \return	The second time.
	 **************************************************************************************************/

	time_t get_second_time() const { return tb_.time; }

	/**********************************************************************************************//**
	 * \brief	Gets the time.
	 *
	 * \return	null if it fails, else the time.
	 **************************************************************************************************/

	const tm* get_tm() const { return &tm_; }

	/**********************************************************************************************//**
	 * \brief	得到当前毫秒.
	 *
	 * \return	The millisecond time.
	 **************************************************************************************************/

	long long get_millisecond_time() const;

	/**********************************************************************************************//**
	 * \brief	得到time是第几天，用于判断是否是同一天.
	 *
	 * \param	time	The time.
	 *
	 * \return	time as an int.
	 **************************************************************************************************/

	int to_days(time_t time);

	/**********************************************************************************************//**
	 * \brief	得到time_是第几天，用于判断是否是同一天.
	 *
	 * \return	This object as an int.
	 **************************************************************************************************/

	int to_days();

	/**********************************************************************************************//**
	 * \brief	得到time是第几周，用于判断是否是同一周.
	 *
	 * \param	time	The time.
	 *
	 * \return	time as an int.
	 **************************************************************************************************/

	int to_weeks(time_t time);

	/**********************************************************************************************//**
	 * \brief	得到time是第几周，用于判断是否是同一周.
	 *
	 * \return	time as an int.
	 **************************************************************************************************/

	int to_weeks();

	/**********************************************************************************************//**
	 * \brief	添加定时器.
	 *
	 * \param [in,out]	timer	If non-null, the timer.
	 **************************************************************************************************/

	void add_timer(GameTimer* timer);

	/**********************************************************************************************//**
	 * \brief	每一帧调用.
	 **************************************************************************************************/

	void tick();

protected:
	tm											tm_;
	timeb										tb_;

	std::priority_queue<GameTimer*, std::vector<GameTimer*>, GameTimerCmp> timers_;
};
