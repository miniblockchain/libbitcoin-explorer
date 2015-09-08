/**
 * Copyright (c) 2011-2015 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin-explorer.
 *
 * libbitcoin-explorer is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License with
 * additional permissions to the one published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version. For more information see LICENSE.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include <bitcoin/explorer/commands/ek-public-to-address.hpp>

#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/primitives/address.hpp>

using namespace bc;
using namespace bc::bip38;
using namespace bc::explorer;
using namespace bc::explorer::commands;
using namespace bc::explorer::primitives;

console_result ek_public_to_address::invoke(std::ostream& output,
    std::ostream& error)
{
    const auto& passphrase = get_passphrase_argument();
    const auto& key = get_ek_public_key_argument();

#ifndef WITH_ICU
    error << BX_EK_PUBLIC_TO_ADDRESS_REQUIRES_ICU << std::endl;
    return console_result::failure;
#endif

    ec_point point;
    uint8_t version;
    if (!decrypt(point, version, key, passphrase))
    {
        error << BX_EK_PUBLIC_TO_ADDRESS_INVALID_PASSPHRASE << std::endl;
        return console_result::failure;
    }

    const address payment_address(version, point);

    output << payment_address << std::endl;
    return console_result::okay;
}

