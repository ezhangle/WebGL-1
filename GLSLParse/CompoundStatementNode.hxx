//--------------------------------------------------------------
//
// Microsoft Edge Implementation
// Copyright(c) Microsoft Corporation
// All rights reserved.
//
// MIT License
//
// Permission is hereby granted, free of charge, to any person obtaining
// a copy of this software and associated documentation files(the ""Software""),
// to deal in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell copies
// of the Software, and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS
// OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
// OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
//--------------------------------------------------------------
#pragma once

#include "CollectionNodeWithScope.hxx"

class TypeQualifierNode;
class VariableIdentifierNode;

//+-----------------------------------------------------------------------------
//
//  Class:      CompoundStatementNode
//
//  Synopsis:   Node information for a compund statement in GLSL.
//
//------------------------------------------------------------------------------
class CompoundStatementNode : public CollectionNodeWithScope
{
public:
    CompoundStatementNode();

    HRESULT Initialize(
        __in CGLSLParser* pParser,                              // The parser that owns the tree
        __in_opt ParseTreeNode* pStatementList,                 // The statement list
        bool fDefinesScope                                      // Whether this node actually defines a scope
        );

    HRESULT Initialize(
        __in CGLSLParser* pParser                               // The parser that owns the tree
        ) { ParseTreeNode::Initialize(pParser); return S_OK; }

    // ParseTreeNode methods
    ParseNodeType::Enum GetParseNodeType() const override { return GetClassNodeType(); }
    HRESULT OutputHLSL(__in IStringStream* pOutput) override;
    HRESULT PreVerifyChildren() override;
    HRESULT GetDumpString(__in IStringStream* pOutput) override;

    bool IsScopeNode(
        __in ParseTreeNode* pTreeNode,                          // Node that scope query is for
        __deref_out_opt ParseTreeNode** ppActual                // Tree node that is the actual scope
        ) override { (*ppActual) = this; return _fDefinesScope; }

    // For GetAs et al
    static ParseNodeType::Enum GetClassNodeType() { return ParseNodeType::compoundStatement; }

private:
    bool _fDefinesScope;                                        // Whether this node actually defines a scope
};
