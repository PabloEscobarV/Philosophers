/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polenyc <polenyc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:40:41 by polenyc           #+#    #+#             */
/*   Updated: 2024/04/30 12:49:32 by polenyc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <thread>
#include <mutex>
#include <iostream>
#include "philo.h"

using namespace std;

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
	Alkash	alkash;

	alkash.finding(1);
	alkash.finding(1);
	

	// Alkash	alkash;
	// Alkash	sobut;
	// Buchlo	buchlo;
	// mutex	mt1;
	// // Timer<float>	time;

	// // time.start();
	// thread	th1([&]()
	// {
	// 	alkash.buchat(buchlo, 2);
	// 	cout << alkash.timer.gettime() << endl;
	// });
	// thread	th2([&]()
	// {
	// 	alkash.buchat(buchlo, 2);
	// 	cout << alkash.timer.gettime() << endl;
	// });

	// th1.join();
	// th2.join();

	// alkash.buchat(buchlo, 5);
	// cout << alkash.timer.gettime() << endl;
	// alkash.buchat(buchlo, 5);
	// cout << alkash.timer.gettime() << endl;

	// time.stop();
	// cout << time << endl;
	// alkash.getBuchlo(buchlo, mt1);
	// sobut.getBuchlo(buchlo, mt1);
	// mutex	mt1;
	// thread	th1(func, ref(mt1));
	// thread	th2(func, ref(mt1));

	// th1.join();
	// th2.join();
	return (0);
}
