#include <list>

#include <plx/data/List.hpp>
#include <plx/data/Queue.hpp>
#include <plx/evaluator/Evaluator.hpp>
#include <plx/object/ThrowException.hpp>

namespace PLX {

    Queue::Queue() {}

    Queue::Queue(std::initializer_list<Object*> elems)
        : Queue()
    {
        enq(elems);
    }

    List* Queue::asList() const {
        return _head;
    }

    bool Queue::boolValue() const {
        return _nElems != 0;
    }

    Object* Queue::deq() {
        if (_nElems == 0) {
            throwException("Queue", "Queue empty", this);
        }
        Object* elem = _head->first();
        _head = _head->restAsList();
        _nElems--;
        return elem;
    }

    void Queue::enq(Object* elem) {
        List* link = new List(elem, GLOBALS->EmptyList());
        if (_tail->isEmpty()) {
            _head = _tail = link;
        }
        else {
            _tail->setRest(link);
            _tail = link;
        }
        _nElems++;
    }

    void Queue::enq(std::initializer_list<Object*> elems) {
        for (Object* elem : elems) {
            enq(elem);
        }
    }

    bool Queue::equals(const Object* other) const {
        if (this == other) {
            return true;
        }
        if (other->isA(TypeId::D_QUEUE)) {
            const Queue* otherQueue = static_cast<const Queue*>(other);
            if (isEmpty()) {
                return otherQueue->isEmpty();
            }
            return _head->equals(otherQueue->_head);
        }
        return false;
    }

    Object* Queue::eval(Evaluator* etor) {
        Queue* newQueue = new Queue();
        List* elems = _head;
        while (!elems->isEmpty()) {
            Object* elem = elems->first();
            Object* value = etor->evalExpr(elem);
            newQueue->enq(value);
            elems = elems->restAsList();
        }
        return newQueue;
    }

    bool Queue::isEmpty() const {
        return _nElems == 0;
    }

    int Queue::length() const {
        return _nElems;
    }

    bool Queue::length(int& len) {
        len = _nElems;
        return true;
    }

    void Queue::markChildren() {
        _head->mark();
    }

    void Queue::showOn(std::ostream& ostream) const {
        ostream << '~' << _head;
    }

    bool Queue::toArray(Array*& array) {
        return _head->toArray(array);
    }

    bool Queue::toList(List*& list) {
        List* elems = _head;
        Queue* queue = new Queue();
        while (!elems->isEmpty()) {
            queue->enq(elems->first());
            elems = elems->restAsList();
        }
        list = queue->asList();
        return true;
    }

    bool Queue::toQueue(Queue*& queue) {
        queue = this;
        return true;
    }

    TypeId Queue::typeId() const {
        return TypeId::D_QUEUE;
    }

}
