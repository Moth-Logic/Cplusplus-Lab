#pragma once

<<<<<<< HEAD:Listas/DNode.h
template <typename E>
=======
template <typename E> 
>>>>>>> 0b582b9dd1e83b191df0609d4a04b255e326069c:Listas_Juli/DNode.h
class DNode {
public:
	E element;
	DNode<E>* next;
<<<<<<< HEAD:Listas/DNode.h
	DNode<E>* previous;
=======
    DNode<E>* previous;
>>>>>>> 0b582b9dd1e83b191df0609d4a04b255e326069c:Listas_Juli/DNode.h

	DNode(E element, DNode<E>* next, DNode<E>* previous) {
		this->element = element;
		this->next = next;
<<<<<<< HEAD:Listas/DNode.h
		this->previous = previous;
	}
	DNode(DNode<E>* next, DNode<E>* previous) {
		this->next = next;
		this->previous = previous;
=======
        this->previous = previous;
	}
	DNode(DNode<E>* next, DNode<E>* previous) {
		this->next = next;
        this->previous = previous;
>>>>>>> 0b582b9dd1e83b191df0609d4a04b255e326069c:Listas_Juli/DNode.h
	}
};