#pragma once

#include "natalie_parser/node/node.hpp"
#include "natalie_parser/node/node_with_args.hpp"
#include "tm/hashmap.hpp"
#include "tm/string.hpp"

namespace NatalieParser {

using namespace TM;

class SuperNode : public NodeWithArgs {
public:
    SuperNode(const Token &token)
        : NodeWithArgs { token } { }

    SuperNode(const SuperNode &other)
        : NodeWithArgs { other }
        , m_parens { other.parens() } { }

    virtual Node *clone() const override {
        return new SuperNode(*this);
    }

    virtual Type type() const override { return Type::Super; }

    virtual bool is_callable() const override { return true; }
    virtual bool can_accept_a_block() const override { return true; }

    bool parens() const { return m_parens; }
    void set_parens(bool parens) { m_parens = parens; }

    bool empty_parens() const { return m_parens && m_args.is_empty(); }

    virtual void transform(Creator *creator) const override {
        if (empty_parens()) {
            creator->set_type("super");
            return;
        } else if (args().is_empty()) {
            creator->set_type("zsuper");
            return;
        }
        creator->set_type("super");
        for (auto arg : args()) {
            creator->append(arg);
        }
    }

protected:
    bool m_parens { false };
};
}
