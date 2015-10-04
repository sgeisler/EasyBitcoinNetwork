//
// Created by sebastian on 26.09.15.
//

#include <ByteArray.h>
#include <Conversions.h>
#include "Message.h"

ByteArray Message::serialize() const
{
    ByteArray ser = Conversions::fromUInt32(this->magic);
    ser += Conversions::fromString(this->command);

    ByteArray data = getPayload();

    ser += Conversions::fromUInt32(data.size());
    ser += data.sha256().sha256().getSection(0, 4);
    ser += data;

    return ser;
}