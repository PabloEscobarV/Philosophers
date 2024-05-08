/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buchlo.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:30:51 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/08 17:07:30 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/buchlo.h"

namespace alkashi_sim
{
    Buchlo::Buchlo(int id_) :
        id(id_),
        status(true)
    {

    }

    Buchlo::Buchlo(const Buchlo& obj)
    {
        id = obj.id;
        status = obj.status;
    }

    Buchlo::~Buchlo()
    {

    }

    Buchlo&	Buchlo::operator=(const Buchlo& obj)
    {
        if (this == &obj)
            return (*this);
        id = obj.id;
        status = obj.status;
        return (*this);
    }

    void	Buchlo::set_id(int _id)
    {
        id = _id;
    }

    int		Buchlo::get_id()
    {
        return (id);
    }

    ostream&	operator<<(ostream& os, const Buchlo& obj)
    {
        os << "BUCHLO ID:\t" << hex << this_thread::get_id() << endl;
        return (os);
    }

    void    Buchlo::lock()
    {
        status = false;
    }

    void	Buchlo::unlock()
    {
        status = true;
    }
    
    bool    Buchlo::state()
    {
        return (status);
    }
}
