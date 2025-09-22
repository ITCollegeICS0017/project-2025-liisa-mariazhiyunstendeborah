#include <iostream>
#include <list>
#include <string>
using namespace std;

class MainClass {
	public:

		enum usertype {
			Receptionist,
			Photographer,
			StAdmin,
		};

		class Material {
		//(material_instance_id, material type, quantity, order_id)
			public:
				int instance_id;
				int order_id;
				enum material_type {
					paper,
					developer,
					//other materials if necessary
				} mat_t;
				int quantity = 0;

				Material(int inst_id, material_type m_t) {
					instance_id = inst_id;
					mat_t = m_t;
				}

				void addMaterials(material_type mat_t, int added_q) {
				//StAdmin adds a quantity of material

				}

				void removeMaterials(material_type mat_t, int subtr_q) {
				//StAdmin removes a quantity of material

				}

		};

		class User {
			public:
				string name;
				int user_id;
				usertype utype;

				User(int u_id, usertype ut) {
				//StAdmin creates a user, User constructor
				//createUser() for now
					user_id = u_id;
					utype = ut;
				}

				~User() {
				//StAdmin deletes a user, User destructor
				//deleteUser() for now

				}

		};

		class Order {
		//(order_id, due_date, price, status, client name, user_id (photographer)
			public:
				list<Material> materials;
				int order_id;
				int user_id;
				string cl_name;
				int due_date;
				int price;
				bool status = false;

				Order(int o_id, string cl_n, int dd, int pr) {
					order_id = o_id;
					cl_name = cl_n;
					due_date = dd;
					price = pr;
				}
				
		};

		
		void assignPhotographer(int order_id, int user_id) {
		//Receptionist assigns a photographer

		}

		Order viewOrder(int order_id) {
		//returns what's in the object Order
			// placeholder return value
			return Order(0, "", 0, 0);
		}

		list<Order> listOrders() {
		//returns current existing list of Orders

			// placeholder return value
			return list<Order>();
		}

		void changeOrderState() {
		//photographer changes the completion
		//status of their order

		}

		//I separated the generation and viewreports by generating
		//user because they have different variables and there is
		//way to unite it.

		pair<list<Order>, int> generateReceptionistReport(){
		//Receptionist generates a report of 
		//completed orders and total revenue
			// placeholder return value
			return pair<list<Order>, int>();
		}

		list<Material> generatePhotographerReport(int order_id){
		//photographer generates a report of consumed materials

			// placeholder return value
			return list<Material>();
		}

		list<pair<list<Order>, int>> viewReceptionistReports() {
		//StAdmin views current submitted receptionist reports

			// placeholder return value
			return list<pair<list<Order>, int>>();
		}

		list<list<Material>> viewPhotographerReports() {
		//StAdmin views current submitted photographer reports
		
			// placeholder return value
			return list<list<Material>>();
		}

		list<Material> listMaterials() {
		//StAdmin lists materials and their 
		//current quantities

			// placeholder return value
			return list<Material>();
		}


		list<Order> orders;
		list<Material> materials;
		list<pair<list<Order>, int>> receptionist_reports;
		list<list<Material>> photographer_reports;
};

int main() {
//receptionist records order
	//arbitrary values
	int recept_id = 0;
	int photog_id = 1;
	int order_id = 0;
	string client_name = "Client Name"; 
	int price = 10; 
	int due_date = 1; 
	//i.e. in 1 workday 
	//(we can decide on exact due_date format later as we will do with the price calculation)
	
	MainClass Main;
	MainClass::User receptionist(recept_id, MainClass::Receptionist);
	MainClass::User photographer(photog_id, MainClass::Photographer);
	MainClass::Order order1(order_id, client_name, due_date, price);
	Main.assignPhotographer(order_id, photog_id); 
}
