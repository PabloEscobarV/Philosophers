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

using namespace std;

void	func(mutex &mt)
{
	mt.lock();
	for (int i = 0; i < 10; ++i)
	{
		this_thread::sleep_for(chrono::milliseconds(10));
		cout << "func[" << i << "]\tID:\t" << hex << this_thread::get_id() << endl;
	}
	cout << "----------------------\n";
	mt.unlock();
}

int		main(void)
{
	mutex	mt;
	thread	th1(func, ref(mt));
	thread	th2(func, ref(mt));

	th1.join();
	th2.join();

	return (0);
}