/* 
 * Copyright (c) 2011-2014, Intel Corporation
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "AnswerMessage.h"
#include "RemoteProcessorProtocol.h"
#include <assert.h>

#define base CMessage

CAnswerMessage::CAnswerMessage(const string& strAnswer, bool bSuccess) : base(bSuccess ? ESuccessAnswer : EFailureAnswer), _strAnswer(strAnswer)
{
}

CAnswerMessage::CAnswerMessage()
{
}

// Answer
void CAnswerMessage::setAnswer(const string& strAnswer)
{
    _strAnswer = strAnswer;
}

const string& CAnswerMessage::getAnswer() const
{
    return _strAnswer;
}

// Status
bool CAnswerMessage::success() const
{
    return getMsgId() == ESuccessAnswer;
}

// Size
uint32_t CAnswerMessage::getDataSize() const
{
    // Answer
    return getStringSize(getAnswer());
}

// Fill data to send
void CAnswerMessage::fillDataToSend()
{
    // Send answer
    writeString(getAnswer());
}

// Collect received data
void CAnswerMessage::collectReceivedData()
{
    // Receive answer
    string strAnswer;

    readString(strAnswer);

    setAnswer(strAnswer);
}
