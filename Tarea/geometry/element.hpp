/**
 *Previammente con el modelo de 2D
 *teniamos solamete un ID y dos nodos,
 *pero en este caso tendriamos 4 nodos.
*/
class Element {
    private:
        short ID;
        Node* node1;
        Node* node2;
        Node* node3;
        Node* node4; 

    public:
        Element (short identifier, Node* first_node, Node* second_node, Node* third_node, Node* fourth_node ){
            ID = identifier;
            node1 = first_node;
            node2 = second_node;
            node3 = third_node;
            node4 = fourth_node;
        }

        void set_ID(short identifier){
            ID = identifier;
        }
        short get_ID(){
            return ID;
        }

        void set_node1(Node* node){
            node1 = node;
        }
        Node* get_node1(){
            return node1;
        }

        void set_node2(Node* node){
            node2 = node;
        }
        Node* get_node2(){
            return node2;
        }

        void set_node3(Node* node){
            node3 = node;
        }
        Node* get_node3(){
            return node3;
        }

        void set_node4(Node* node){
            node4 = node;
        }
        Node* get_node4(){
            return node4;
        }

        Node* get_node_i(int i){
            
            if(i=1){
                return node1;
            } else if(i = 2){
                return node2;
            }else if(i = 3){
                return node3;
            }else if(i = 4){
                return node4;
            }

        }

        Node* set_node_i(int i, Node* node){
            
            if(i=1){
                node1 = node;
            } else if(i = 2){
                node2 = node;
            }else if(i = 3){
                node3 = node;
            }else if(i = 4){
                node4 = node;
            }

        }
};