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
#pragma once

#include "ConfigurableElement.h"
#include "TypeElement.h"

class IMapper;
class CParameterBlackboard;
class CParameterAccessContext;

class CInstanceConfigurableElement : public CConfigurableElement
{
public:
    enum Type {
        EBitParameter,
        EBitParameterBlock,
        EParameter,
        EStringParameter,
        EParameterBlock,
        EComponent
    };

    CInstanceConfigurableElement(const string& strName, const CTypeElement* pTypeElement);

    // Instantiated type
    const CTypeElement* getTypeElement() const;

    bool getMappingData(const string& strKey, const string*& pStrValue) const;

    /**
     * Returns the mapping data associated to the type element of the current
     * InstanceConfigurableElement, as a formatted string
     *
     * @return A string containing the formatted mapping
     */
    string getFormattedMapping() const;

    // From CElement
    virtual string getKind() const;

    // Syncer to/from HW
    void setSyncer(ISyncer* pSyncer);
    void unsetSyncer();

    // Type
    virtual Type getType() const = 0;

    // Mapping execution
    bool map(IMapper& mapper, string& strError);

    // Element properties
    virtual void showProperties(string& strResult) const;

    // Scalar or Array?
    bool isScalar() const;

    // Array Length
    uint32_t getArrayLength() const;

    /**
     * Get the list of all the ancestors that have a mapping.
     *
     * The mapping is represented as a string of all the mapping data (key:value) defined in the
     * context of the element.
     * In this class, the method is generic and calls its parent getListOfElementsWithMappings(...)
     * method.
     *
     * @param[in:out] configurableElementPath List of all the ConfigurableElements found
     * that have a mapping. Elements are added at the end of the list, so the root Element will be
     * the last one.
     */
    virtual void getListOfElementsWithMapping(list<const CConfigurableElement*>&
                                               configurableElementPath) const;
protected:
    // Syncer
    virtual ISyncer* getSyncer() const;
    // Syncer set (descendant)
    virtual void fillSyncerSetFromDescendant(CSyncerSet& syncerSet) const;
    // Sync
    bool sync(CParameterAccessContext& parameterAccessContext) const;
    // Check parameter access path well formed for leaf elements
    static bool checkPathExhausted(CPathNavigator& pathNavigator, CErrorContext& errorContext);
private:
    // Type Element
    const CTypeElement* _pTypeElement;

    // Sync to HW
    ISyncer* _pSyncer;
};

