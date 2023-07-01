/**
 *Mesh significa que a través de arreglos de nodos se puedan
 *guardar detos de un archivo
 */
#include "node.hpp"
#include "element.hpp"
/**
 * Las clases que ya cambiaron pero que sus condiones se mantienen son las de Node y Element.
 */
#include "condition.hpp"
/**
 * Para mesh es indiferente si estamos habland0o de 1D, 2D o 3D.
 */


/**
 *Lo que hace meesh es que almacena las condiciones, elementos y nodos, junto con la administración,
 *sin importar que fuera de una dimensión, de dos dimensiones o hasta 3D, de esas 3 clases.
*/
enum parameter {THERMAL_CONDUCTIVITY, HEAT_SOURCE};
enum quantity {NUM_NODES, NUM_ELEMENTS, NUM_DIRICHLET, NUM_NEUMANN};

class Mesh {
    private:
        float problem_data[2];
        short quantities[4];
        int j = 0;
        Node** nodes;
        Element** elements;         
        Condition** dirichlet_conditions;
        Condition** neumann_conditions;

    public:
        Mesh(){}

        ~Mesh(){
            free(nodes);
            free(elements);
            free(dirichlet_conditions);
            free(neumann_conditions);
        }

        void set_problem_data(float k, float Q){
            problem_data[THERMAL_CONDUCTIVITY] = k;
            problem_data[HEAT_SOURCE] = Q;
        }
        float get_problem_data(parameter position){
            return problem_data[position];
        }

        void set_quantities(short num_nodes, short num_elements, short num_dirichlet, short num_neumann){
            quantities[NUM_NODES] = num_nodes;
            quantities[NUM_ELEMENTS] = num_elements;
            quantities[NUM_DIRICHLET] = num_dirichlet;
            quantities[NUM_NEUMANN] = num_neumann;
        }
        short get_quantity(quantity position){
            return quantities[position];
        }

        void init_arrays(){
            nodes = (Node**) malloc(sizeof(Node*) * quantities[NUM_NODES]);
            elements = (Element**) malloc(sizeof(Element*) * quantities[NUM_ELEMENTS]);
            dirichlet_conditions = (Condition**) malloc(sizeof(Condition*) * quantities[NUM_DIRICHLET]);
            neumann_conditions = (Condition**) malloc(sizeof(Condition*) * quantities[NUM_NEUMANN]);
        }

        void insert_node(Node* node, short position){
            nodes[position] = node;
        }

        void heap_sort_nodes(Element* element){

            Element* temporary = element;
            Node* item;
            Node* temp;

            for(int k = 4 ; k>0 ; k--){
                for(int i = 1 ; i <= k ; i-- ){
                    item = element->get_node_i(k);
                    j = i/2;
                    while(j>0 && element->get_node_i(j) < item){
                        element->set_node_i(i, element->get_node_i(j));
                        i = j;
                        j = j/2;
                    }
                element->set_node_i(i, item);
                }
                temp = element->get_node1();
                element->set_node1(element->get_node_i(k));
                element->set_node_i(k, temp);
            }

        }

        Node* get_node(short position){
            return nodes[position];
        }

        void insert_element(Element* element, short position){
            elements[position] = element;
        }
        Element* get_element(short position){
            return elements[position];
        }

        void insert_dirichlet_condition(Condition* dirichlet_condition, short position){
            dirichlet_conditions[position] = dirichlet_condition;
        }
        Condition* get_dirichlet_condition(short position){
            return dirichlet_conditions[position];
        }
        bool does_node_have_dirichlet_condition(int id){
            bool ans = false;
            for(int i = 0; i < quantities[NUM_DIRICHLET]; i++)
                if(dirichlet_conditions[i]->get_node()->get_ID() == id){
                    ans = true;
                    break;
                }
            return ans;
        }

        void insert_neumann_condition(Condition* neumann_condition, short position){
            neumann_conditions[position] = neumann_condition;
        }
        Condition* get_neumann_condition(short position){
            return neumann_conditions[position];
        }

        void report(){
            cout << "Problem Data\n**********************\n";
            cout << "Thermal Conductivity: " << problem_data[THERMAL_CONDUCTIVITY] << "\n";
            cout << "Heat Source: " << problem_data[HEAT_SOURCE] << "\n\n";
            cout << "Quantities\n***********************\n";
            cout << "Number of nodes: " << quantities[NUM_NODES] << "\n";
            cout << "Number of elements: " << quantities[NUM_ELEMENTS] << "\n";
            cout << "Number of dirichlet boundary conditions: " << quantities[NUM_DIRICHLET] << "\n";
            cout << "Number of neumann boundary conditions: " << quantities[NUM_NEUMANN] << "\n\n";
            cout << "List of nodes\n**********************\n";
            for(int i = 0; i < quantities[NUM_NODES]; i++){
                cout << "Node: " << nodes[i]->get_ID() << ", x= " << nodes[i]->get_x_coordinate() << ", y= " << nodes[i]->get_y_coordinate() << "\n";
                cout << ", z= " << nodes[i]->get_z_coordinate() ;
            }
            cout << "\nList of elements\n**********************\n";
            for(int i = 0; i < quantities[NUM_ELEMENTS]; i++){
                cout << "Element: " << elements[i]->get_ID() << ", Node 1= " << elements[i]->get_node1()->get_ID();
                cout << ", Node 2= " << elements[i]->get_node2()->get_ID() << ", Node 3= " << elements[i]->get_node3()->get_ID() << "\n";
                cout << ", Node 4= " << elements[i]->get_node4()->get_ID();
            }
            cout << "\nList of Dirichlet boundary conditions\n**********************\n";
            for(int i = 0; i < quantities[NUM_DIRICHLET]; i++)
                cout << "Condition " << i+1 << ": " << dirichlet_conditions[i]->get_node()->get_ID() << ", Value= " << dirichlet_conditions[i]->get_value() << "\n";
            cout << "\nList of Neumann boundary conditions\n**********************\n";
            for(int i = 0; i < quantities[NUM_NEUMANN]; i++)
                cout << "Condition " << i+1 << ": " << neumann_conditions[i]->get_node()->get_ID() << ", Value= " << neumann_conditions[i]->get_value() << "\n";
            cout << "\n";
        }
};