#pragma once

#include "natalie_parser/creator.hpp"
#include "natalie_parser/token.hpp"

namespace NatalieParser {

class NodeWithArgs;

class Node {
public:
    enum class Type {
        Invalid,
        Alias,
        Arg,
        Array,
        ArrayPattern,
        Assignment,
        BackRef,
        Begin,
        BeginRescue,
        Bignum,
        Block,
        BlockPass,
        Break,
        Call,
        Case,
        CaseIn,
        CaseWhen,
        Class,
        Colon2,
        Colon3,
        Constant,
        Def,
        Defined,
        EvaluateToString,
        False,
        Fixnum,
        Float,
        Hash,
        HashPattern,
        Identifier,
        If,
        InfixOp,
        Iter,
        InterpolatedRegexp,
        InterpolatedShell,
        InterpolatedString,
        InterpolatedSymbol,
        KeywordArg,
        KeywordSplat,
        LogicalAnd,
        LogicalOr,
        Match,
        Module,
        MultipleAssignment,
        MultipleAssignmentArg,
        Next,
        Nil,
        NilSexp,
        Not,
        NotMatch,
        NthRef,
        OpAssign,
        OpAssignAccessor,
        OpAssignAnd,
        OpAssignOr,
        Pin,
        Range,
        Regexp,
        Return,
        SafeCall,
        Sclass,
        Self,
        Shell,
        Splat,
        SplatValue,
        StabbyProc,
        String,
        Super,
        Symbol,
        ToArray,
        True,
        UnaryOp,
        Undef,
        Until,
        While,
        Yield,
    };

    Node() { }

    Node(const Token &token)
        : m_token { token } { }

    Node(const Node &) = delete;
    Node &operator=(const Node &) = delete;

    virtual ~Node() { }

    virtual Type type() const { return Type::Invalid; }

    virtual bool is_callable() const { return false; }
    virtual bool is_numeric() const { return false; }
    virtual bool can_accept_a_block() const { return false; }

    virtual Node *clone() const {
        if (type() == Type::Invalid)
            printf("Trying to clone() an invalid Node\n");
        else
            printf("Need to implement Node::clone() in a subclass (type=%d)...\n", (int)type());
        TM_UNREACHABLE();
    }

    virtual void transform(Creator *creator) const {
        creator->set_type("NOT_YET_IMPLEMENTED");
        creator->append_integer((int)type());
    }

    SharedPtr<String> file() const { return m_token.file(); }
    size_t line() const { return m_token.line(); }
    size_t column() const { return m_token.column(); }

    Optional<SharedPtr<String>> doc() const { return m_token.doc(); }

    const Token &token() const { return m_token; }

    const static Node &invalid() {
        if (!s_invalid)
            s_invalid = new Node;
        return *s_invalid;
    }

    operator bool() const {
        return type() != Type::Invalid;
    }

    NodeWithArgs *to_node_with_args();

protected:
    static inline Node *s_invalid { nullptr };
    Token m_token {};
};

}
