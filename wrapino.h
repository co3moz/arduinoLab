class WrapinoNode {
public:
	WrapinoNode* next;
	Wrapino* Wrapino;
	
	WrapinoNode() {
		this-> next = NULL;
		this-> Wrapino = NULL;
	}
	
	~WrapinoNode() {
		if(this-> Wrapino != NULL) {
			delete Wrapino;
		}

		if(this-> next != NULL) {
			delete next;
		} 
	}

	WrapinoNode* add(Wrapino* Wrapino) {
		if(this-> Wrapino == NULL) {
			this-> Wrapino = Wrapino;
			return this;
		}
		return this-> next-> add(Wrapino); 
	}
}

class Wrapino {
public:
	static WrapinoNode* node;
	Wrapino() {
		node-> add(this);
	}

	setup() {

	}

	loop() {

	}
};
Wrapino::node = new WrapinoNode();