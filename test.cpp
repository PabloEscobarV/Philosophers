/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polenyc <polenyc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:40:41 by polenyc           #+#    #+#             */
/*   Updated: 2024/04/26 14:48:49 by polenyc          ###   ########.fr       */
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
	Alkash	sobut;
	Buchlo	buchlo;
	mutex	mt1;
	mutex	mt2;
	thread	th1([&](){ alkash.getBuchlo(buchlo, mt1); });
	thread	th2([&](){ sobut.getBuchlo(buchlo, mt1); });

	th1.join();
	th2.join();
	// alkash.getBuchlo(buchlo, mt1);
	// sobut.getBuchlo(buchlo, mt1);
	// mutex	mt1;
	// thread	th1(func, ref(mt1));
	// thread	th2(func, ref(mt1));

	// th1.join();
	// th2.join();
	return (0);
}