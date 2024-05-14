#include <plx/data/Array.hpp>
#include <plx/evaluator/Evaluator.hpp>
#include <plx/expr/IndexOp.hpp>
#include <plx/literal/Symbol.hpp>
#include <plx/object/ThrowException.hpp>

namespace PLX {

    IndexOp::IndexOp(Object* collection, Object* index)
        : _collection {collection}
        , _index {index}
    {}

    Object* IndexOp::eval(Evaluator* etor) {
        Object* collectionValue = etor->evalExpr(_collection);
        Object* indexValue = etor->evalExpr(_index);
        Object* retrievedValue;
        if (!collectionValue->index(indexValue, retrievedValue)) {
            throwException("Index", "Object is not indexable", 
                new Array({collectionValue, collectionValue->typeSymbol()}));
        }
        return retrievedValue;
    }

    void IndexOp::markChildren() {
        _collection->mark();
        _index->mark();
    }

    void IndexOp::showOn(std::ostream& ostream) const {
        ostream << _collection << '[' << _index << ']';
    }

    TypeId IndexOp::typeId() const {
        return TypeId::E_INDEXOP;
    }

}
