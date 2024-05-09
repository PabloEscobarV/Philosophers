/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:40:41 by polenyc           #+#    #+#             */
/*   Updated: 2024/05/09 15:07:03 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <thread>
#include <mutex>
#include <iostream>
#include "../hdrs/philo.h"

using namespace std;
using namespace alkashi_sim;

void	func(mutex &mt1)
{
	mt1.lock();
	for (int i = 0; i < 10; ++i)
	{
		this_thread::sleep_for(chrono::milliseconds(10));
		cout << "func[" << i << "]\tID:\t" << hex << this_thread::get_id() << endl;
	}
	cout << "----------------------\n";
	mt1.unlock();
}

int		main(void)
{
	// t_uchar	mask = 8;
	// t_uchar	bit = 7;
	// t_uchar	val = 1;

	// mask |= val << bit;
	// // mask <<= bit;
	// for (int i = 0; i < 8; ++i)
	// 	cout << "BIT[" << i << "]: " << (mask & (val << i)) << endl;
	Timer<float>	timer;
	timer.start();
	TaskPlanner	planer(111, 100, 200, 441);

	planer.startplanner();
	// planer.startsimulation();
	// planer.startsimplanner();
	cout << "EXECUTION TIME: " << timer.gettime() << endl;
	// Alkash	alkash{1};
	// Alkash	sobut{2};
	// Buchlo	buchlo;
	// mutex	mt1;

	// thread	th1([&]()
	// {
	// 	alkash.buchat(buchlo, mt1, 1000);
	// 	alkash.sleep(mt1, 1000);
	// 	alkash.finding(mt1);
	// });
	// thread	th2([&]()
	// {
	// 	sobut.buchat(buchlo, mt1, 1000);
	// 	sobut.sleep(mt1, 1000);
	// 	sobut.finding(mt1);
	// });

	// th1.join();
	// th2.join();
	// cout << "The whole time for alkash:\t" << alkash.timer.gettime() << endl;
	// cout << "The whole time for sobut:\t" << sobut.timer.gettime() << endl;
	return (0);
}
