#ifndef PROTOTYPE_HPP
#define PROTOTYPE_HPP

// Interface Prototype
template<typename T>
class Prototype {
public:
    virtual T* clonar() const = 0;
    virtual ~Prototype() {}
};

#endif