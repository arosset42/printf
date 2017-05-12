/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arosset <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/12 15:11:20 by arosset           #+#    #+#             */
/*   Updated: 2017/05/12 16:16:28 by arosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void    ft_print_str(t_args *cylva)
{
    int     total;

    total = ft_str_max_print(cylva);
    if (cylva->operation == 's' && cylva->m_lenght == '0')
    {
        total == 0 ? ft_put_len_str(NULL, -1) : ft_put_len_str(cylva->str, total);
    }
    else if (cylva->operation == 'c')
        ft_putchar(cylva->c);
    else if (cylva->operation == 'S' || (cylva->m_lenght == 'l' && cylva->operation == 's'))
    {
        if (total == -1)
        {
            ft_put_len_str(NULL, -1);
            total = 6;
        }
        ft_putwstr(cylva->wstr, total);
    }
    else
        ft_putwchar(cylva->wchar);
    cylva->len_print += total > cylva->width ? total : cylva->width;
    if (cylva->f_moins == 1)
    {
        ft_put_len_str(" ", cylva->width - total);
    }
}

void	ft_print_nbr(t_args *cylva, long long int nbr)
{
    int     max;

    if (!nbr && S_OPE != 'o' && S_OPE != 'O')
        cylva->f_diese = 0;
    if (!nbr && S_PREC == -1 && S_OPE == 'o' && cylva->f_diese == 1)
        S_PREC = 0;
    max = ft_nbr_max_print(nbr, cylva);
    cylva->len_print += BIGGER(max, BIGGER(cylva->width, cylva->precision));
    ft_print_arg_nbr(cylva, max, nbr);
    if (cylva->base == 16 && S_OPE == 'X')
        cylva->base = 1;
    if (S_OPE == '%')
        write(1, "%", 1);
    if ((nbr || S_PREC) && S_OPE != '%')
        ft_print_base(cylva, nbr);
    if (cylva->f_moins == 1 && cylva->width > cylva->precision)
        ft_put_n_char(' ', cylva->width - max);
}

void    ft_print_arg_nbr(t_args *cylva, int max, long long int nbr)
{
    if (((S_ZERO == 1 || S_MOINS == 1) || (S_ZERO == 1 && S_PREC >= 0)))
        ft_put_n_char(' ', cylva->width - max);
    if ((S_SPACE == 1 ) && S_OPE != '%')
        write(1, " ", 1);
    if ((S_PLUS == 1 ) && S_OPE != '%')
            write(1, "+", 1);
    if ((S_DIESE == 1 && (S_OPE == 'X' || S_OPE == 'x')) || S_OPE == 'p')
        S_OPE == 'X' ? write(1, "0X", 2) : write(1, "0x", 2);
    if (S_DIESE == 1 && (S_OPE == 'o' || S_OPE == 'O'))
    {
        write(1, "0", 1);
        S_PREC -= S_PREC > 0 ? 1 : 0;
    }
    if (cylva->f_diese == '0' && S_PREC == -1)
        ft_put_n_char('0', cylva->width - max);
    if (S_PREC > 0)
        ft_put_n_char('0', S_PREC - nblen(nbr, cylva->base));
}

void    ft_print_base(t_args *cylva, long long int nbr)
{
    char	*out;

    if (cylva->base == 1)
        cylva->base = -16;
    if (ft_str_index("dDi", S_OPE) != -1)
        out = (nbr == -9223372036854775807 - 1) ?
            ft_strdup("-9223372036854775808") : ft_itoa_base(nbr, cylva->base);
    else
        out = ft_uitoa_base((unsigned long long int)nbr, cylva->base);
    ft_put_len_str(out, ft_strlen(out));
    ft_memdel((void *)&out);
}
