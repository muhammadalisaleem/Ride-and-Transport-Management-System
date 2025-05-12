/*
Transport & Ride Management System

Ali Saleem (23L-2638)
Shahmeer Iqbal (22L-7471)
*/


#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class Name {
private:
	char* fName; // First Name
	char* lName; // Last Name

public:
	// Default Constructor
	Name() : fName(nullptr), lName(nullptr) {}

	// Parameterized Constructor
	Name(const char* fN, const char* lN) {
		fName = new char[strlen(fN) + 1];
		lName = new char[strlen(lN) + 1];
		strcpy_s(fName, strlen(fN) + 1, fN);
		strcpy_s(lName, strlen(lN) + 1, lN);
	}

	// Copy Constructor
	Name(const Name& other) {
		fName = new char[strlen(other.fName) + 1];
		lName = new char[strlen(other.lName) + 1];
		strcpy_s(fName, strlen(other.fName) + 1, other.fName);
		strcpy_s(lName, strlen(other.lName) + 1, other.lName);
	}

	// Destructor
	~Name() {
		delete[] fName;
		delete[] lName;
	}

	// Getter for First Name
	const char* getFirstName() const {
		return fName;
	}

	// Getter for Last Name
	const char* getLastName() const {
		return lName;
	}

	// Setter for First Name
	void setFirstName(const char* fN) {
		delete[] fName; // Free existing memory
		fName = new char[strlen(fN) + 1];
		strcpy_s(fName, strlen(fN) + 1, fN);
	}

	// Setter for Last Name
	void setLastName(const char* lN) {
		delete[] lName; // Free existing memory
		lName = new char[strlen(lN) + 1];
		strcpy_s(lName, strlen(lN) + 1, lN);
	}

	// Friend function to overload << operator
	friend ostream& operator<<(ostream& out, const Name& n);
};

// Overloaded << operator
ostream& operator<<(ostream& out, const Name& n) {
	out << n.fName << " " << n.lName;
	return out;
}

class Date {
private:
	int day;
	int month;
	int year;

public:
	// Default Constructor
	Date() : day(1), month(1), year(2000) {}

	// Parameterized Constructor
	Date(int d, int m, int y) : day(d), month(m), year(y) {}

	// Getter for Day
	int getDay() const {
		return day;
	}

	// Getter for Month
	int getMonth() const {
		return month;
	}

	// Getter for Year
	int getYear() const {
		return year;
	}

	// Setter for Day
	void setDay(int d) {
		day = d;
	}

	// Setter for Month
	void setMonth(int m) {
		month = m;
	}

	// Setter for Year
	void setYear(int y) {
		year = y;
	}

	// Function to output the date in the format day / Mon / Year
	void outputDate() const {
		const char* months[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun",
								  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
		cout << day << " / " << months[month - 1] << " / " << year;
	}

	bool operator==(const Date& other) const {
		return (this->day == other.day && this->month == other.month && this->year == other.year);
	}


	// Friend function to overload << operator
	friend ostream& operator<<(ostream& out, const Date& d);

	friend istream& operator>>(istream& in, Date& d);
};

// Overloaded << operator
ostream& operator<<(ostream& out, const Date& d) {
	const char* months[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun",
0							  ,"Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
	out << d.day << " / " << months[d.month - 1] << " / " << d.year;
	return out;
}

// Overloaded >> operator
istream& operator>>(istream& in, Date& d) {
	char slash; // To consume the '/' characters in the input
	in >> d.day >> slash >> d.month >> slash >> d.year;
	return in;
}

class mTime {
private:
	int hour;
	int min;
	int sec;

public:
	// Default Constructor
	mTime() : hour(0), min(0), sec(0) {}

	// Parameterized Constructor
	mTime(int h, int m, int s) : hour(h), min(m), sec(s) {
		// Normalize time
		normalize();
	}

	// Getter for Hour
	int getHour() const {
		return hour;
	}

	// Getter for Minute
	int getMin() const {
		return min;
	}

	// Getter for Second
	int getSec() const {
		return sec;
	}

	// Setter for Hour
	void setHour(int h) {
		hour = h;
		normalize();
	}

	// Setter for Minute
	void setMin(int m) {
		min = m;
		normalize();
	}

	// Setter for Second
	void setSec(int s) {
		sec = s;
		normalize();
	}

	// Function to normalize time
	void normalize() {
		if (sec >= 60) {
			min += sec / 60;
			sec = sec % 60;
		}
		if (min >= 60) {
			hour += min / 60;
			min = min % 60;
		}
		// Assuming 24-hour format
		hour = hour % 24;
	}

	// Friend function to overload << operator
	friend ostream& operator<<(ostream& out, const mTime& t);
};

// Overloaded << operator
ostream& operator<<(ostream& out, const mTime& t) {
	out << t.hour << " : " << t.min << " : " << t.sec;
	return out;
}

class Service {
private:
	char* source;
	char* destination;
	float distance; // in km
	Date bookingDate;
	mTime bookingTime;
	bool status; // false for pending, true if complete
	float fuelRate;
	int cId; // Customer Id who booked the ride
	int dId; // Driver Id
	int vId; // Vehicle Id
	int id;  // Combined ID (defined dynamically)

	void calculateId() {
		id = (cId * 10000) + (vId * 100) + dId; // Unique formula for ID
	}

public:
	// Constructor
	Service(const char* src, const char* dest, float dist, const Date& bDate, const mTime& bTime,
		bool stat, float fRate, int customerId, int driverId, int vehicleId)
		: distance(dist), bookingDate(bDate), bookingTime(bTime), status(stat),
		fuelRate(fRate), cId(customerId), dId(driverId), vId(vehicleId) {
		source = new char[strlen(src) + 1];
		strcpy_s(source, strlen(src) + 1, src);
		destination = new char[strlen(dest) + 1];
		strcpy_s(destination, strlen(dest) + 1, dest);
	}

	// Destructor
	~Service() {
		delete[] source;
		delete[] destination;
	}

	// Getters
	const char* getSource() const {
		return source;
	}

	const char* getDestination() const {
		return destination;
	}

	float getDistance() const {
		return distance;
	}

	Date getBookingDate() const {
		return bookingDate;
	}

	mTime getBookingTime() const {
		return bookingTime;
	}

	bool getStatus() const {
		return status;
	}

	float getFuelRate() const {
		return fuelRate;
	}

	int getId() const { 
		return id; 
	}

	int getCustomerId() const {
		return cId;
	}

	int getDriverId() const {
		return dId;
	}

	int getVehicleId() const {
		return vId;
	}

	// Setters
	void setSource(const char* src) {
		delete[] source;
		source = new char[strlen(src) + 1];
		strcpy_s(source, strlen(src) + 1, src);
	}

	void setDestination(const char* dest) {
		delete[] destination;
		destination = new char[strlen(dest) + 1];
		strcpy_s(destination, strlen(dest) + 1, dest);
	}

	void setDistance(float dist) {
		distance = dist;
	}

	void setBookingDate(const Date& bDate) {
		bookingDate = bDate;
	}

	void setBookingTime(const mTime& bTime) {
		bookingTime = bTime;
	}

	void setStatus(bool stat) {
		status = stat;
	}

	void setFuelRate(float fRate) {
		fuelRate = fRate;
	}

	void setCustomerId(int customerId) {
		cId = customerId;
	}

	void setDriverId(int driverId) {
		dId = driverId;
	}

	void setVehicleId(int vehicleId) {
		vId = vehicleId;
	}
	// Member function to display service details
	void displayServiceDetails() const {
		cout << "Service Details:" << endl;
		cout << "Source: " << source << endl;
		cout << "Destination: " << destination << endl;
		cout << "Distance: " << distance << " km" << endl;
		cout << "Booking Date: " << bookingDate << endl;
		cout << "Booking Time: " << bookingTime << endl;
		cout << "Status: " << (status ? "Complete" : "Pending") << endl;
		cout << "Fuel Rate: " << fuelRate << " per km" << endl;
		cout << "Customer ID: " << cId << endl;
		cout << "Driver ID: " << dId << endl;
		cout << "Vehicle ID: " << vId << endl;
	}

	// Overloaded output operator
	friend ostream& operator<<(ostream& os, const Service& service) {
		os << "Service Details:" << endl;
		os << "Source: " << service.source << endl;
		os << "Destination: " << service.destination << endl;
		os << "Distance: " << service.distance << " km" << endl;
		os << "Booking Date: " << service.bookingDate << endl;
		os << "Booking Time: " << service.bookingTime << endl;
		os << "Status: " << (service.status ? "Complete" : "Pending") << endl;
		os << "Fuel Rate: " << service.fuelRate << " per km" << endl;
		os << "Customer ID: " << service.cId << endl;
		os << "Driver ID: " << service.dId << endl;
		os << "Vehicle ID: " << service.vId << endl;
		return os;
	}
};

class Ride : public Service {
private:
	int noOfPassengers; // Number of passengers
	char* rideType;     // "intercity", "intracity"
	float driverRanking; // 0 to 5 scale (worst to best)
	float vehicleRanking; // 0 to 5 scale (worst to best)

public:
	// Constructor
	Ride(const char* src, const char* dest, float dist, const Date& bDate, const mTime& bTime,
		bool stat, float fRate, int customerId, int driverId, int vehicleId,
		int passengers, const char* type, float dRanking, float vRanking)
		: Service(src, dest, dist, bDate, bTime, stat, fRate, customerId, driverId, vehicleId),
		noOfPassengers(passengers), driverRanking(dRanking), vehicleRanking(vRanking) {
		rideType = new char[strlen(type) + 1];
		strcpy_s(rideType, strlen(type) + 1, type);
	}

	// Destructor
	~Ride() {
		delete[] rideType;
	}

	// Getters
	int getNoOfPassengers() const {
		return noOfPassengers;
	}

	const char* getRideType() const {
		return rideType;
	}

	float getDriverRanking() const {
		return driverRanking;
	}

	float getVehicleRanking() const {
		return vehicleRanking;
	}

	// Setters
	void setNoOfPassengers(int passengers) {
		noOfPassengers = passengers;
	}

	void setRideType(const char* type) {
		delete[] rideType;
		rideType = new char[strlen(type) + 1];
		strcpy_s(rideType, strlen(type) + 1, type);
	}

	void setDriverRanking(float ranking) {
		driverRanking = ranking;
	}

	void setVehicleRanking(float ranking) {
		vehicleRanking = ranking;
	}

	// Member function to display ride details
	void displayRideDetails() const {
		displayServiceDetails();
		cout << "Number of Passengers: " << noOfPassengers << endl;
		cout << "Ride Type: " << rideType << endl;
		cout << "Driver Ranking: " << driverRanking << endl;
		cout << "Vehicle Ranking: " << vehicleRanking << endl;
	}
};

class Delivery : public Service {
private:
	float goodsWeight; // Weight of goods in Kg
	char* goodsType;   // Type of goods (e.g., food, furniture, petroleum, chemicals, etc.)

public:
	// Constructor
	Delivery(const char* src, const char* dest, float dist, const Date& bDate, const mTime& bTime,
		bool stat, float fRate, int customerId, int driverId, int vehicleId,
		float weight, const char* type)
		: Service(src, dest, dist, bDate, bTime, stat, fRate, customerId, driverId, vehicleId),
		goodsWeight(weight) {
		goodsType = new char[strlen(type) + 1];
		strcpy_s(goodsType, strlen(type) + 1, type);
	}
	// Destructor
	~Delivery() {
		delete[] goodsType;
	}

	// Getters
	float getGoodsWeight() const {
		return goodsWeight;
	}

	const char* getGoodsType() const {
		return goodsType;
	}

	// Setters
	void setGoodsWeight(float weight) {
		goodsWeight = weight;
	}

	void setGoodsType(const char* type) {
		delete[] goodsType;
		goodsType = new char[strlen(type) + 1];
		strcpy_s(goodsType, strlen(type) + 1, type);
	}

	// Member function to display delivery details
	void displayDeliveryDetails() const {
		displayServiceDetails();
		cout << "Goods Weight: " << goodsWeight << " Kg" << endl;
		cout << "Goods Type: " << goodsType << endl;
	}
};

class Person {
private:
	Name pName;
	Date DOB;
	int age;    // Age of the person
	int nid;    // National ID

public:
	// Default Constructor
	Person() : age(0), nid(0) {

	}

	// Parameterized Constructor
	Person(const Name& name, const Date& dob, int age, int nid)
		: pName(name), DOB(dob), age(age), nid(nid) {}

	// Copy Constructor
	Person(const Person& other)
		: pName(other.pName), DOB(other.DOB), age(other.age), nid(other.nid) {}

	// Destructor
	~Person() {}

	// Getters
	Name getName() const {
		return pName;
	}

	Date getDOB() const {
		return DOB;
	}

	int getAge() const {
		return age;
	}

	int getNid() const {
		return nid;
	}

	// Setters
	void setName(const Name& name) {
		pName = name;
	}

	void setDOB(const Date& dob) {
		DOB = dob;
	}

	void setAge(int age) {
		this->age = age;
	}

	void setNid(int nid) {
		this->nid = nid;
	}

	// Overloaded output operator
	friend ostream& operator<<(ostream& os, const Person& person) {
		os << "Name: " << person.pName << endl;
		os << "Date of Birth: " << person.DOB << endl;
		os << "Age: " << person.age << endl;
		os << "National ID: " << person.nid << endl;
		return os;
	}
};

class Customer : public Person {
private:
	int cId; // customer ID
	Service** bookingHistory; // Dynamic array for service bookings
	int historyCount; // Number of bookings made

public:
	// Default Constructor
	Customer() : cId(0), bookingHistory(nullptr), historyCount(0) {}

	// Parameterized Constructor
	Customer(const Name& name, const Date& dob, int age, int nid, int customerId)
		: Person(name, dob, age, nid), cId(customerId), bookingHistory(nullptr), historyCount(0) {}

	// Copy Constructor
	Customer(const Customer& other) : Person(other), cId(other.cId), historyCount(other.historyCount) {
		if (other.bookingHistory) {
			bookingHistory = new Service * [other.historyCount];
			for (int i = 0; i < other.historyCount; i++) {
				bookingHistory[i] = other.bookingHistory[i];
			}
		}
		else {
			bookingHistory = nullptr;
		}
	}

	// Destructor
	~Customer() {
		delete[] bookingHistory;
	}

	// Getters
	int getCustomerId() const {
		return cId;
	}

	Service** getBookingHistory() const {
		return bookingHistory;
	}

	int getHistoryCount() const {
		return historyCount;
	}

	// Setters
	void setCustomerId(int customerId) {
		cId = customerId;
	}

	// Function to add a booking to the history
	void addBooking(Service* service) {
		Service** newHistory = new Service * [historyCount + 1];
		for (int i = 0; i < historyCount; i++) {
			newHistory[i] = bookingHistory[i];
		}
		newHistory[historyCount] = service;
		delete[] bookingHistory;
		bookingHistory = newHistory;
		historyCount++;
	}

	// Overloaded output operator
	friend ostream& operator<<(ostream& os, const Customer& customer) {
		os << static_cast<const Person&>(customer);
		os << "Customer ID: " << customer.cId << endl;
		os << "Booking History: " << customer.historyCount << " bookings" << endl;
		for (int i = 0; i < customer.historyCount; i++) {
			os << "Booking " << (i + 1) << ": " << *(customer.bookingHistory[i]) << endl;
		}
		return os;
	}
};

class Driver : public Person {
private:
	int dId; // Driver ID
	char** licensesList; // Dynamic array for licenses
	int noOfLicenses; // Number of licenses
	float overallRanking; // Overall ranking of the driver
	float salary; // Salary of the driver
	int experience; // Years of experience
	int status; // 1 for free, 2 if booked, 3 if canceled
	Service** serviceHistory; // Dynamic array for service history
	int serviceCount; // Number of services completed

public:
	// Default Constructor
	Driver() : dId(0), licensesList(nullptr), noOfLicenses(0), overallRanking(0), salary(0), experience(0), status(1), serviceHistory(nullptr), serviceCount(0) {}

	// Parameterized Constructor
	Driver(const Name& name, const Date& dob, int age, int nid, int driverId, float salary, int experience)
		: Person(name, dob, age, nid), dId(driverId), licensesList(nullptr), noOfLicenses(0), overallRanking(0), salary(salary), experience(experience), status(1), serviceHistory(nullptr), serviceCount(0) {}

	// Copy Constructor
	Driver(const Driver& other) : Person(other), dId(other.dId), overallRanking(other.overallRanking), salary(other.salary), experience(other.experience), status(other.status), serviceCount(other.serviceCount) {
		// Copy licenses
		if (other.noOfLicenses > 0) {
			licensesList = new char* [other.noOfLicenses];
			for (int i = 0; i < other.noOfLicenses; i++) {
				licensesList[i] = new char[strlen(other.licensesList[i]) + 1];
				strcpy_s(licensesList[i], strlen(other.licensesList[i]) + 1, other.licensesList[i]);
			}
			noOfLicenses = other.noOfLicenses;
		}
		else {
			licensesList = nullptr;
			noOfLicenses = 0;
		}

		// Copy service history
		if (other.serviceHistory) {
			serviceHistory = new Service * [other.serviceCount];
			for (int i = 0; i < other.serviceCount; i++) {
				serviceHistory[i] = other.serviceHistory[i];
			}
		}
		else {
			serviceHistory = nullptr;
		}
	}

	// Destructor
	~Driver() {
		for (int i = 0; i < noOfLicenses; i++) {
			delete[] licensesList[i];
		}
		delete[] licensesList;
		delete[] serviceHistory;
	}

	// Getters
	int getDriverId() const {
		return dId;
	}

	char** getLicensesList() const {
		return licensesList;
	}

	int getNoOfLicenses() const {
		return noOfLicenses;
	}

	float getOverallRanking() const {
		return overallRanking;
	}

	float getSalary() const {
		return salary;
	}

	int getExperience() const {
		return experience;
	}

	int getStatus() const {
		return status;
	}

	Service** getServiceHistory() const {
		return serviceHistory;
	}

	int getServiceCount() const {
		return serviceCount;
	}

	// Setters
	void setDriverId(int driverId) {
		dId = driverId;
	}

	void setStatus(int stat) {
		status = stat;
	}

	void setDriverRanking(float rank) {
		overallRanking = rank;
	}
	void setNoOfLicenses(int n_Licecnse) {
		noOfLicenses = n_Licecnse;
	}

	void addLicense(const char* license) {
		char** newLicensesList = new char* [noOfLicenses + 1];
		for (int i = 0; i < noOfLicenses; i++) {
			newLicensesList[i] = licensesList[i];
		}
		newLicensesList[noOfLicenses] = new char[strlen(license) + 1];
		strcpy_s(newLicensesList[noOfLicenses], strlen(license) + 1, license);
		delete[] licensesList;
		licensesList = newLicensesList;
		noOfLicenses++;
	}

	// Function to add a service to the history
	void addService(Service* service) {
		Service** newHistory = new Service * [serviceCount + 1];
		for (int i = 0; i < serviceCount; i++) {
			newHistory[i] = serviceHistory[i];
		}
		newHistory[serviceCount] = service;
		delete[] serviceHistory;
		serviceHistory = newHistory;
		serviceCount++;
	}

	// Overloaded output operator
	friend ostream& operator<<(ostream& os, const Driver& driver) {
		os << static_cast<const Person&>(driver);
		os << "Driver ID: " << driver.dId << endl;
		os << "Licenses: " << driver.noOfLicenses << " licenses" << endl;
		for (int i = 0; i < driver.noOfLicenses; i++) {
			os << "License " << (i + 1) << ": " << driver.licensesList[i] << endl;
		}
		os << "Overall Ranking: " << driver.overallRanking << endl;
		os << "Salary: " << driver.salary << endl;
		os << "Experience: " << driver.experience << " years" << endl;
		os << "Status: " << driver.status << endl;
		os << "Service History: " << driver.serviceCount << " services" << endl;
		for (int i = 0; i < driver.serviceCount; i++) {
			os << "Service " << (i + 1) << ": " << *(driver.serviceHistory[i]) << endl;
		}
		return os;
	}
};

class Feature {
private:
	int fId;               // Feature ID
	char* description;     // Dynamic string for feature description
	float cost;            // Cost of the feature

public:
	// Default Constructor
	Feature() : fId(0), description(nullptr), cost(0.0f) {}

	// Parameterized Constructor
	Feature(int id, const char* desc, float c) : fId(id), cost(c) {
		description = new char[strlen(desc) + 1];
		strcpy_s(description, strlen(desc) + 1, desc);
	}

	// Copy Constructor
	Feature(const Feature& other) : fId(other.fId), cost(other.cost) {
		if (other.description) {
			description = new char[strlen(other.description) + 1];
			strcpy_s(description, strlen(other.description) + 1, other.description);
		}
		else {
			description = nullptr;
		}
	}

	// Destructor
	~Feature() {
		delete[] description;
	}

	// Getters
	int getFeatureId() const {
		return fId;
	}

	const char* getDescription() const {
		return description;
	}

	float getCost() const {
		return cost;
	}

	// Setters
	void setFeatureId(int id) {
		fId = id;
	}

	void setDescription(const char* desc) {
		delete[] description;
		description = new char[strlen(desc) + 1];
		strcpy_s(description, strlen(desc) + 1, desc);
	}

	void setCost(float c) {
		cost = c;
	}

	// Overloaded output operator
	friend ostream& operator<<(ostream& os, const Feature& feature) {
		os << "Feature ID: " << feature.fId << endl;
		os << "Description: " << (feature.description ? feature.description : "N/A") << endl;
		os << "Cost: " << feature.cost << endl;
		return os;
	}
};

class Vehicle {
protected:
	int vId;                   // Vehicle ID
	int registrationNo;        // Vehicle registration number
	float avgMileage;          // Average mileage of the vehicle
	char* licenseType;         // License required for driving the vehicle
	bool status;               // false for free, true if booked in a service already
	char* fuelType;            // Fuel type of the vehicle
	float overallRanking;      // Overall ranking of the vehicle
	Date manufacturingDate;    // Manufacturing date of the vehicle
	Feature* list;             // List of features
	vector<Service*> serviceHistory; // Dynamic array for service history

public:
	// Default Constructor
	Vehicle() : vId(0), registrationNo(0), avgMileage(0.0f), status(false), overallRanking(0.0f), list(nullptr) {
		licenseType = nullptr;
		fuelType = nullptr;
	}

	// Parameterized Constructor
	Vehicle(int id, int regNo, float mileage, const char* licType, const char* fuel, float ranking, const Date& manuDate)
		: vId(id), registrationNo(regNo), avgMileage(mileage), status(false), overallRanking(ranking), manufacturingDate(manuDate), list(nullptr) {
		licenseType = new char[strlen(licType) + 1];
		strcpy_s(licenseType, strlen(licType) + 1, licType);

		fuelType = new char[strlen(fuel) + 1];
		strcpy_s(fuelType, strlen(fuel) + 1, fuel);
	}

	// Copy Constructor
	Vehicle(const Vehicle& other) : vId(other.vId), registrationNo(other.registrationNo), avgMileage(other.avgMileage),
		status(other.status), overallRanking(other.overallRanking), manufacturingDate(other.manufacturingDate), list(other.list) {
		// Copy licenseType
		if (other.licenseType) {
			licenseType = new char[strlen(other.licenseType) + 1];
			strcpy_s(licenseType, strlen(other.licenseType) + 1, other.licenseType);
		}
		else {
			licenseType = nullptr;
		}

		// Copy fuelType
		if (other.fuelType) {
			fuelType = new char[strlen(other.fuelType) + 1];
			strcpy_s(fuelType, strlen(other.fuelType) + 1, other.fuelType);
		}
		else {
			fuelType = nullptr;
		}

		// Copy service history
		serviceHistory = other.serviceHistory;
	}

	// Destructor
	virtual ~Vehicle() {
		delete[] licenseType;
		delete[] fuelType;

	}

	// Getters
	int getVehicleId() const { return vId; }
	int getRegistrationNo() const { return registrationNo; }
	float getAvgMileage() const { return avgMileage; }
	const char* getLicenseType() const { return licenseType; }
	bool getStatus() const { return status; }
	const char* getFuelType() const { return fuelType; }
	float getOverallRanking() const { return overallRanking; }
	const Date& getManufacturingDate() const { return manufacturingDate; }
	const vector<Service*>& getServiceHistory() const { return serviceHistory; }

	// Setters
	void setVehicleId(int id) { vId = id; }
	void setRegistrationNo(int regNo) { registrationNo = regNo; }
	void setAvgMileage(float mileage) { avgMileage = mileage; }
	void setLicenseType(const char* licType) {
		delete[] licenseType;
		licenseType = new char[strlen(licType) + 1];
		strcpy_s(licenseType, strlen(licType) + 1, licType);
	}
	void setStatus(bool stat) { status = stat; }
	void setFuelType(const char* fuel) {
		delete[] fuelType;
		fuelType = new char[strlen(fuel) + 1];
		strcpy_s(fuelType, strlen(fuel) + 1, fuel);
	}
	void setOverallRanking(float ranking) { overallRanking = ranking; }
	void setManufacturingDate(const Date& manuDate) { manufacturingDate = manuDate; }

	// Function to add a service to the service history
	void addService(Service* service) {
		serviceHistory.push_back(service);
	}

	// Virtual function to display vehicle details
	virtual void display() const {
		cout << "Vehicle ID: " << vId << endl;
		cout << "Registration No: " << registrationNo << endl;
		cout << "Average Mileage: " << avgMileage << endl;
		cout << "License Type: " << (licenseType ? licenseType : "N/A") << endl;
		cout << "Status: " << (status ? "Booked" : "Available") << endl;
		cout << "Fuel Type: " << (fuelType ? fuelType : "N/A") << endl;
		cout << "Overall Ranking: " << overallRanking << endl;
		cout << "Manufacturing Date: " << manufacturingDate << endl;
		cout << "Service History Count: " << serviceHistory.size() << endl;
	}
};

class Car : public Vehicle {
private:
	int numberOfDoors; // Number of doors in the car

public:
	Car(int id, int regNo, float mileage, const char* licType, const char* fuel, float ranking, const Date& manuDate, int doors)
		: Vehicle(id, regNo, mileage, licType, fuel, ranking, manuDate), numberOfDoors(doors) {}

	void display() const override {
		Vehicle::display();
		cout << "Number of Doors: " << numberOfDoors << endl;
	}
};

class Truck : public Vehicle {
private:
	float loadCapacity;

public:
	Truck(int id, int regNo, float mileage, const char* licType, const char* fuel, float ranking, const Date& manuDate, float capacity)
		: Vehicle(id, regNo, mileage, licType, fuel, ranking, manuDate), loadCapacity(capacity) {}

	void display() const {
		Vehicle::display();
		cout << "Load Capacity: " << loadCapacity << " tons" << endl;
	}
};

class Motorcycle : public Vehicle {
private:
	bool hasSidecar; // Indicates if the motorcycle has a sidecar

public:
	Motorcycle(int id, int regNo, float mileage, const char* licType, const char* fuel, float ranking, const Date& manuDate, bool sidecar)
		: Vehicle(id, regNo, mileage, licType, fuel, ranking, manuDate), hasSidecar(sidecar) {}

	void display() const override {
		Vehicle::display(); // Call base class display
		cout << "Has Sidecar: " << (hasSidecar ? "Yes" : "No") << endl;
	}
};

class TMS {
private:
	Customer* customers[15]; // Array of Customers
	Driver* drivers[10];      // Array of Drivers
	Vehicle* vehicles[20];    // Array of Vehicles
	Service** services;        // Dynamic array of Services
	int customerCount;
	int driverCount;
	int vehicleCount;
	int serviceCount;

public:
	TMS() : customerCount(0), driverCount(0), vehicleCount(0), serviceCount(0) {
		services = new Service * [100]; // Allocate memory for services
	}

	~TMS() {
		for (int i = 0; i < customerCount; i++) {
			delete customers[i];
		}
		for (int i = 0; i < driverCount; i++) {
			delete drivers[i];
		}
		for (int i = 0; i < vehicleCount; i++) {
			delete vehicles[i];
		}
		for (int i = 0; i < serviceCount; i++) {
			delete services[i];
		}
		delete[] services;
	}

	void displayMenu() {
		cout << endl;
		cout << "___________________________________________________________________________ " << endl;
		cout << "|------------------- Ride & Transport Management System ------------------| " << endl;
		cout << "|-------------------------------------------------------------------------| " << endl;
		cout << "|  1.  Add a new Customer                                                 | " << endl;
		cout << "|  2.  Add a Driver.                                                      | " << endl;
		cout << "|  3.  Remove a Driver.                                                   | " << endl;
		cout << "|  4.  Add a Vehicle.                                                     | " << endl;
		cout << "|  5.  Remove a Vehicle.                                                  | " << endl;
		cout << "|  6.  Print List of All Customers.                                       | " << endl;
		cout << "|  7.  Print List of All Drivers.                                         | " << endl;
		cout << "|  8.  Print complete list of vehicles with details by their category.    | " << endl;
		cout << "|  9.  Print complete details and service history of a particular vehicle.| " << endl;
		cout << "|  10. Print complete history of a particular customer.                   | " << endl;
		cout << "|  11. Print complete history of a driver including services.             | " << endl;
		cout << "|  12. Print list of all drivers who have ranking above 4.5.              | " << endl;
		cout << "|  13. Print list of all drivers who have multiple licenses.              | " << endl;
		cout << "|  14. Print updated salary of all drivers based on their updated ranking.| " << endl;
		cout << "|  15. Add a Service request (ride or delivery) for a customer.           | " << endl;
		cout << "|  16. Cancel a booking.                                                  | " << endl;
		cout << "|  17. Complete a service.                                                | " << endl;
		cout << "|  18. Print details of Customers who used the same vehicle               | " << endl;
		cout << "|      in a ride service on a different date.                             | " << endl;
		cout << "|  19. Print the List of all Drivers who completed delivery services      | " << endl;
		cout << "|      on same days.                                                      | " << endl;
		cout << "|  20. Print details of all pending services on a particular date.        | " << endl;
		cout << "|  21. Print details of all pending services of a particular driver.      | " << endl;
		cout << "|  22. Print details of all canceled services by a customer.              | " << endl;
		cout << "|  0. Exit.                                                               | " << endl;
		cout << "|_________________________________________________________________________| " << endl;
		cout << "Select an option: ";

	}

	void addCustomer() {
		if (customerCount >= 15) {
			cout << "Customer limit reached!" << endl;
			return;
		}

		char fName[50], lName[50];
		cout << "Enter First Name: ";
		cin >> fName;
		cout << "Enter Last Name: ";
		cin >> lName;

		int cid;
		cout << "Enter Customer ID: ";
		cin >> cid;

		Name name(fName, lName);

		int day, month, year;
		cout << "Enter Date of Birth (DD MM YYYY): ";
		cin >> day >> month >> year;
		Date dob(day, month, year);

		int age, nid;
		cout << "Enter Age: ";
		cin >> age;
		cout << "Enter National ID: ";
		cin >> nid;

		Customer* newCustomer = new Customer(name, dob, age, nid, cid);
		customers[customerCount++] = newCustomer;

		cout << "Customer added successfully!" << endl;

		// Open the file in append mode to add the new customer
		ofstream outFile("customers.txt", ios::app);
		if (outFile.is_open()) {
			
			outFile << fName << " "
				<< lName << " "
				<< cid << " "
				<< day << " " << month << " " << year << " "
				<< age << " "
				<< nid << endl;

			outFile.close();
			cout << "Customer data saved to file successfully!" << endl;
		}
		else {
			cout << "Unable to open customers.txt for writing!" << endl;
		}
	}


	void addDriver() {
		if (driverCount >= 10) {
			cout << "Driver limit reached!" << endl;
			return;
		}

		char fName[50], lName[50];
		cout << "Enter First Name: ";
		cin >> fName;
		cout << "Enter Last Name: ";
		cin >> lName;

		Name name(fName, lName);

		int day, month, year;
		cout << "Enter Date of Birth (DD MM YYYY): ";
		cin >> day >> month >> year;
		Date dob(day, month, year);

		int age, nid, driverId, experience;
		float salary;

		cout << "Enter Age: ";
		cin >> age;
		cout << "Enter National ID: ";
		cin >> nid;
		cout << "Enter Driver ID: ";
		cin >> driverId;
		cout << "Enter Salary: ";
		cin >> salary;
		cout << "Enter Years of Experience: ";
		cin >> experience;

		Driver* newDriver = new Driver(name, dob, age, nid, driverId, salary, experience);
		drivers[driverCount++] = newDriver;

		cout << "Driver added successfully!" << endl;

		// Open the file in append mode to add the new driver
		ofstream outFile("drivers.txt", ios::app);
		if (outFile.is_open()) {
			
			outFile << fName << " "
				<< lName << " "
				<< driverId << " "
				<< age << " "
				<< nid << " "
				<< salary << " "
				<< experience << " "
				<< day << " " << month << " " << year << endl;

			outFile.close();
			cout << "Driver data saved to file successfully!" << endl;
		}
		else {
			cout << "Unable to open drivers.txt for writing!" << endl;
		}
	}


	void removeDriver() {
		int driverId;
		cout << "Enter Driver ID to remove: ";
		cin >> driverId;

		for (int i = 0; i < driverCount; i++) {
			if (drivers[i]->getDriverId() == driverId) {
				delete drivers[i];
				drivers[i] = drivers[--driverCount];

				// After removing, update the drivers.txt file
				ofstream outFile("drivers.txt");
				if (outFile.is_open()) {

					for (int j = 0; j < driverCount; j++) {
						outFile << drivers[j]->getDriverId() << ","
							<< drivers[j]->getName().getFirstName() << ","
							<< drivers[j]->getName().getLastName() << ","
							<< drivers[j]->getAge() << ","
							<< drivers[j]->getSalary() << ","
							<< drivers[j]->getExperience() << endl;
					}
					outFile.close();
					cout << "Driver removed successfully and data updated in file!" << endl;
				}
				else {
					cout << "Unable to open drivers.txt for writing!" << endl;
				}
				return;
			}
		}

		cout << "Driver not found!" << endl;
	}


	void addVehicle() {
		if (vehicleCount >= 20) {
			cout << "Vehicle limit reached!" << endl;
			return;
		}

		int id, regNo;
		float mileage, ranking;
		char licType[50], fuel[50];
		int day, month, year;

		cout << "Enter Vehicle ID: ";
		cin >> id;
		cout << "Enter Registration No: ";
		cin >> regNo;
		cout << "Enter Average Mileage: ";
		cin >> mileage;
		cout << "Enter License Type: ";
		cin >> licType;
		cout << "Enter Fuel Type: ";
		cin >> fuel;
		cout << "Enter Overall Ranking: ";
		cin >> ranking;
		cout << "Enter Manufacturing Date (DD MM YYYY): ";
		cin >> day >> month >> year;

		Date manuDate(day, month, year);
		vehicles[vehicleCount++] = new Car(id, regNo, mileage, licType, fuel, ranking, manuDate, 4);
		cout << "Vehicle added successfully!" << endl;

		ofstream outFile("vehicles.txt", ios::app);
		if (outFile.is_open()) {
			outFile << id << " "
				<< regNo << " "
				<< licType << " "
				<< fuel << " "
				<< day << " " << month << " " << year << endl;

			outFile.close();
			cout << "Vehicle data saved to file successfully!" << endl;
		}
		else {
			cout << "Unable to open vehicles.txt for writing!" << endl;
		}
	}


	void removeVehicle() {
		int vehicleId;
		cout << "Enter Vehicle ID to remove: ";
		cin >> vehicleId;

		bool found = false;
		for (int i = 0; i < vehicleCount; i++) {
			if (vehicles[i]->getVehicleId() == vehicleId) {
				delete vehicles[i];
				vehicles[i] = vehicles[--vehicleCount];
				found = true;
				break;
			}
		}

		if (!found) {
			cout << "Vehicle with ID " << vehicleId << " not found!" << endl;
			return;
		}

		ofstream outFile("vehicles.txt", ios::trunc);
		if (outFile.is_open()) {
			for (int i = 0; i < vehicleCount; i++) {
				outFile << vehicles[i]->getVehicleId() << " "
					<< vehicles[i]->getRegistrationNo() << " "
					<< vehicles[i]->getLicenseType() << " "
					<< vehicles[i]->getFuelType() << " "
					<< vehicles[i]->getManufacturingDate().getDay() << " "
					<< vehicles[i]->getManufacturingDate().getMonth() << " "
					<< vehicles[i]->getManufacturingDate().getYear() << endl;
			}
			outFile.close();
			cout << "Vehicle removed and file updated successfully!" << endl;
		}
		else {
			cout << "Unable to open vehicles.txt for writing!" << endl;
		}
	}


	void printAllCustomers() {
		ifstream inFile("customers.txt");
		if (!inFile) {
			cout << "Unable to open customers.txt file!" << endl;
			return;
		}

		cout << "List of All Customers:" << endl;
		char fName[50], lName[50];
		int cid, age, nid, day, month, year;

		while (inFile >> fName >> lName >> cid >> day >> month >> year >> age >> nid) {

			Name name(fName, lName);
			Date dob(day, month, year);

			Customer* customer = new Customer(name, dob, age, nid, cid);

			cout << *customer << endl;

		}

		inFile.close();
	}

	void printAllDrivers() {
		ifstream inFile("drivers.txt");
		if (!inFile) {
			cout << "Unable to open drivers.txt file!" << endl;
			return;
		}

		cout << "List of All Drivers:" << endl;
		char fName[50], lName[50];
		int driverId, age, nid, experience, day, month, year;
		float salary;

		while (inFile >> fName >> lName >> driverId >> age >> nid >> salary >> experience >> day >> month >> year) {

			Name name(fName, lName);
			Date dob(day, month, year);

			Driver* driver = new Driver(name, dob, age, nid, driverId, salary, experience);
			cout << *driver << endl;

			delete driver; 
		}

		if (inFile.eof()) {
			cout << "Reached end of file." << endl;
		}
		else if (inFile.fail()) {
			cout << "File read error or format mismatch occurred!" << endl;
		}

		inFile.close();
	}


	void printAllVehicles() {
		ifstream inFile("vehicles.txt");
		if (!inFile) {
			cout << "Unable to open vehicles.txt file!" << endl;
			return;
		}

		cout << "Complete List of Vehicles:" << endl;
		int id, regNo, day, month, year;
		float mileage, ranking;
		char licType[50], fuel[50];

		while (inFile >> id >> regNo >> mileage >> licType >> fuel >> ranking >> day >> month >> year) {
			Date manuDate(day, month, year);

			Vehicle* vehicle = new Car(id, regNo, mileage, licType, fuel, ranking, manuDate, 4);
			vehicle->display();
			delete vehicle; // Clean up memory
		}

		if (inFile.eof()) {
			cout << "End of file reached." << endl;
		}
		else if (inFile.fail()) {
			cout << "File read error or format mismatch occurred!" << endl;
		}

		inFile.close();
	}


	void printVehicleDetails() {
		int vehicleId;
		cout << "Enter Vehicle ID: ";
		cin >> vehicleId;

		ifstream inFile("vehicles.txt");
		if (!inFile) {
			cout << "Unable to open vehicles.txt file!" << endl;
			return;
		}

		bool found = false;
		int id, regNo;
		float mileage, ranking;
		char licType[50], fuel[50];
		int day, month, year;

		while (inFile >> id >> regNo >> mileage >> licType >> fuel >> ranking >> day >> month >> year) {

			if (id == vehicleId) {
				Date manuDate(day, month, year);
				Vehicle* vehicle = new Car(id, regNo, mileage, licType, fuel, ranking, manuDate, 4);

				cout << "Vehicle Details:" << endl;
				vehicle->display();

				delete vehicle; // Free allocated memory
				found = true;
				break;
			}
		}

		if (!found) {
			cout << "Vehicle with ID " << vehicleId << " not found!" << endl;
		}

		if (inFile.eof()) {
			cout << "Reached end of file." << endl;
		}
		else if (inFile.fail()) {
			cout << "File read error or format mismatch occurred!" << endl;
		}

		inFile.close();
	}


	void printCustomerHistory() {
		int customerId;
		cout << "Enter Customer ID: ";
		cin >> customerId;

		ifstream inFile("customers.txt");
		if (!inFile) {
			cout << "Unable to open customers.txt file!" << endl;
			return;
		}

		bool found = false;
		int id, age, nid;
		char fName[50], lName[50];
		int day, month, year;

		while (inFile >> id >> fName >> lName >> age >> nid >> day >> month >> year) {
	
			if (id == customerId) {
				Name name(fName, lName);
				Date dob(day, month, year);

				Customer* customer = new Customer(name, dob, age, nid, id);
				cout << *customer << endl;
				found = true;

				delete customer; // Free allocated memory
				break;
			}
		}

		if (!found) {
			cout << "Customer with ID " << customerId << " not found!" << endl;
		}

		inFile.close();
	}


	void printDriverHistory() {
		int driverId;
		cout << "Enter Driver ID: ";
		cin >> driverId;

		ifstream inFile("drivers.txt");
		if (!inFile) {
			cout << "Unable to open drivers.txt file!" << endl;
			return;
		}

		bool found = false;
		int id, age, nid, experience, day, month, year;
		float salary;
		char fName[50], lName[50];

		while (inFile >> id >> fName >> lName >> age >> nid >> salary >> experience >> day >> month >> year) {
		
			if (id == driverId) {
				Name name(fName, lName);
				Date dob(day, month, year);

				Driver* driver = new Driver(name, dob, age, nid, id, salary, experience);
				cout << *driver << endl;
				found = true;

				delete driver; // Free allocated memory
				break;
			}
		}

		if (!found) {
			cout << "Driver with ID " << driverId << " not found!" << endl;
		}

		inFile.close();
	}


	void printDriversAboveRanking() {
		cout << "Drivers with ranking above 4.5:" << endl;

		ifstream inFile("drivers.txt");
		if (!inFile) {
			cout << "Unable to open drivers.txt file!" << endl;
			return;
		}

		int id, age, nid;
		float salary, ranking;
		int experience, day, month, year;
		char fName[50], lName[50];

		bool found = false;

		while (inFile >> id >> fName >> lName >> age >> nid >> salary >> experience >> ranking >> day >> month >> year) {
			if (ranking > 4.5) {
				Name name(fName, lName);
				Date dob(day, month, year);

				Driver* driver = new Driver(name, dob, age, nid, id, salary, experience);

				cout << *driver << endl;
				found = true;

				delete driver; // Free allocated memory
			}
		}

		if (!found) {
			cout << "No drivers found with ranking above 4.5!" << endl;
		}

		inFile.close();
	}


	void printDriversWithMultipleLicenses() {
		cout << "Drivers with multiple licenses:" << endl;

		ifstream inFile("drivers.txt");
		if (!inFile) {
			cout << "Unable to open drivers.txt file!" << endl;
			return;
		}

		int id, age, nid, noOfLicenses;
		float salary, ranking;
		int experience, day, month, year;
		char fName[50], lName[50];

		bool found = false;

		while (inFile >> id >> fName >> lName >> age >> nid >> salary >> experience >> ranking >> noOfLicenses >> day >> month >> year) {
			if (noOfLicenses > 1) {
				Name name(fName, lName);
				Date dob(day, month, year);

				Driver* driver = new Driver(name, dob, age, nid, id, salary, experience);
				driver->setNoOfLicenses(noOfLicenses);

				cout << *driver << endl;
				found = true;

				delete driver; // Free allocated memory after use
			}
		}

		if (!found) {
			cout << "No drivers found with multiple licenses!" << endl;
		}

		inFile.close();
	}



	void updateDriverSalaries() {
		cout << "Updated salaries of all drivers based on their ranking:" << endl;

		ifstream inFile("drivers.txt");
		if (!inFile) {
			cout << "Unable to open drivers.txt file!" << endl;
			return;
		}

		int id, age, nid, noOfLicenses;
		float salary, ranking;
		int experience, day, month, year;
		char fName[50], lName[50];

		ofstream outFile("drivers_updated.txt");
		if (!outFile) {
			cout << "Unable to open drivers_updated.txt file!" << endl;
			inFile.close();  
			return;
		}

		while (inFile >> id >> fName >> lName >> age >> nid >> salary >> experience >> ranking >> noOfLicenses >> day >> month >> year) {
			// Calculate the new salary based on ranking
			float newSalary = salary * (1 + (ranking - 3) / 10.0f);

			// Print the updated salary for the driver
			cout << "Driver ID: " << id << ", New Salary: " << newSalary << endl;

			// Write the updated driver information to the output file
			outFile << id << " " << fName << " " << lName << " " << age << " " << nid << " "
				<< newSalary << " " << experience << " " << ranking << " " << noOfLicenses
				<< " " << day << " " << month << " " << year << endl;
		}

		inFile.close();  
		outFile.close(); 

		// Replace the original file with the updated file
		if (remove("drivers.txt") != 0) {
			cout << "Error deleting original drivers.txt file!" << endl;
			return;
		}

		if (rename("drivers_updated.txt", "drivers.txt") != 0) {
			cout << "Error renaming drivers_updated.txt to drivers.txt!" << endl;
		}
		else {
			cout << "Driver salaries updated successfully!" << endl;
		}
	}


	void addServiceRequest() {
		int customerId;
		cout << "Enter Customer ID: ";
		cin >> customerId;

		Customer* customer = nullptr;
		for (int i = 0; i < customerCount; i++) {
			if (customers[i]->getCustomerId() == customerId) {
				customer = customers[i];
				break;
			}
		}

		if (!customer) {
			cout << "Customer not found!" << endl;
			return;
		}

		cout << "Available Vehicles:" << endl;
		bool vehicleFound = false;
		for (int i = 0; i < vehicleCount; i++) {
			if (!vehicles[i]->getStatus()) {
				vehicles[i]->display();
				vehicleFound = true;
			}
		}
		if (!vehicleFound) {
			cout << "No available vehicles!" << endl;
			return;
		}

		cout << "Available Drivers:" << endl;
		bool driverFound = false;
		for (int i = 0; i < driverCount; i++) {
			if (drivers[i]->getStatus() == 1) { // Check if driver is free
				cout << *(drivers[i]) << endl;
				driverFound = true;
			}
		}
		if (!driverFound) {
			cout << "No available drivers!" << endl;
			return;
		}

		int vehicleId, driverId;
		cout << "Enter Vehicle ID for the service: ";
		cin >> vehicleId;
		cout << "Enter Driver ID for the service: ";
		cin >> driverId;

		// Verify if the selected vehicle and driver are available
		bool vehicleAvailable = false, driverAvailable = false;
		for (int i = 0; i < vehicleCount; i++) {
			if (vehicles[i]->getVehicleId() == vehicleId && !vehicles[i]->getStatus()) {
				vehicleAvailable = true;
				break;
			}
		}

		for (int i = 0; i < driverCount; i++) {
			if (drivers[i]->getDriverId() == driverId && drivers[i]->getStatus() == 1) {
				driverAvailable = true;
				break;
			}
		}

		if (!vehicleAvailable || !driverAvailable) {
			cout << "Either the selected vehicle or driver is not available." << endl;
			return;
		}

		int serviceType;
		cout << "Select Service Type (1 for Ride, 2 for Delivery): ";
		cin >> serviceType;

		if (serviceType != 1 && serviceType != 2) {
			cout << "Invalid service type!" << endl;
			return;
		}

		float distance, fuelRate;
		cout << "Enter Distance (in km): ";
		cin >> distance;
		if (distance <= 0) {
			cout << "Invalid distance!" << endl;
			return;
		}
		cout << "Enter Fuel Rate: ";
		cin >> fuelRate;
		if (fuelRate <= 0) {
			cout << "Invalid fuel rate!" << endl;
			return;
		}

		int day, month, year, hour, min, sec;
		cout << "Enter Booking Date (DD MM YYYY): ";
		cin >> day >> month >> year;
		Date bookingDate(day, month, year);
		cout << "Enter Booking Time (HH MM SS): ";
		cin >> hour >> min >> sec;
		mTime bookingTime(hour, min, sec);

		ofstream serviceFile("serviceRequests.txt", ios::app);
		if (!serviceFile) {
			cout << "Unable to open file!" << endl;
			return;
		}

		// Write service request details to the file
		serviceFile << customerId << " " << vehicleId << " " << driverId << " "
			<< serviceType << " " << distance << " " << fuelRate << " "
			<< day << " " << month << " " << year << " " << hour << " " << min << " " << sec << " ";

		if (serviceType == 1) { // Ride
			int passengers;
			char rideType[50];
			cout << "Enter Number of Passengers: ";
			cin >> passengers;
			cout << "Enter Ride Type: ";
			cin >> rideType;

			services[serviceCount++] = new Ride("Source", "Destination", distance, bookingDate, bookingTime, false, fuelRate, customerId, driverId, vehicleId, passengers, rideType, 0, 0);
			serviceFile << "Ride " << passengers << " " << rideType << endl;
		}
		else { // Delivery
			float weight;
			char goodsType[50];
			cout << "Enter Goods Weight (in Kg): ";
			cin >> weight;
			cout << "Enter Goods Type: ";
			cin >> goodsType;

			services[serviceCount++] = new Delivery("Source", "Destination", distance, bookingDate, bookingTime, false, fuelRate, customerId, driverId, vehicleId, weight, goodsType);
			serviceFile << "Delivery " << weight << " " << goodsType << endl;
		}

		// Update vehicle and driver status
		for (int i = 0; i < vehicleCount; i++) {
			if (vehicles[i]->getVehicleId() == vehicleId) {
				vehicles[i]->setStatus(true); // Mark vehicle as booked
				break;
			}
		}

		for (int i = 0; i < driverCount; i++) {
			if (drivers[i]->getDriverId() == driverId) {
				drivers[i]->setStatus(2); // Mark driver as booked
				break;
			}
		}

		serviceFile.close();

		cout << "Service request added successfully!" << endl;
	}


	void cancelBooking() {
		int serviceId;
		cout << "Enter Service ID to cancel: ";
		cin >> serviceId;

		for (int i = 0; i < serviceCount; i++) {
			if (services[i]->getCustomerId() == serviceId) {
				float fare = services[i]->getDistance() * services[i]->getFuelRate(); // Calculate fare
				float cancellationFee = fare * 0.05; // 5% cancellation fee
				cout << "Cancellation fee: " << cancellationFee << endl;

				// Update vehicle and driver status in the file
				for (int j = 0; j < vehicleCount; j++) {
					if (vehicles[j]->getVehicleId() == services[i]->getVehicleId()) {
						vehicles[j]->setStatus(false); // Mark vehicle as free
						break;
					}
				}

				for (int j = 0; j < driverCount; j++) {
					if (drivers[j]->getDriverId() == services[i]->getDriverId()) {
						drivers[j]->setStatus(1); // Mark driver as free
						break;
					}
				}

				// Remove service from history
				delete services[i];
				services[i] = services[--serviceCount];

				// Save updated status in file
				ofstream vehicleFile("vehicles.txt");
				if (!vehicleFile) {
					cout << "Unable to open vehicle file!" << endl;
					return;
				}

				vehicleFile.close();

				// Update the drivers file
				ofstream driverFile("drivers.txt");
				if (!driverFile) {
					cout << "Unable to open driver file!" << endl;
					return;
				}

				driverFile.close();

				// Update the services file
				ofstream serviceFile("serviceRequests.txt");
				if (!serviceFile) {
					cout << "Unable to open service requests file!" << endl;
					return;
				}
				for (int j = 0; j < serviceCount; j++) {
					serviceFile << services[j]->getCustomerId() << " "
						<< services[j]->getCustomerId() << " "
						<< services[j]->getVehicleId() << " "
						<< services[j]->getDriverId() << " " << endl;
				}
				serviceFile.close();

				cout << "Booking canceled successfully!" << endl;
				return;
			}
		}
		cout << "Service not found!" << endl;
	}

	void completeService() {
		int serviceId;
		cout << "Enter Service ID to complete: ";
		cin >> serviceId;

		bool found = false;
		for (int i = 0; i < serviceCount; i++) {
			if (services[i]->getId() == serviceId) {  // Use serviceId instead of customerId
				found = true;

				services[i]->setStatus(true); // Mark service as complete

				// Update customer, driver, and vehicle service records
				for (int j = 0; j < customerCount; j++) {
					if (customers[j]->getCustomerId() == services[i]->getCustomerId()) {
						customers[j]->addBooking(services[i]); // Add service to customer history
						break;
					}
				}

				for (int j = 0; j < driverCount; j++) {
					if (drivers[j]->getDriverId() == services[i]->getDriverId()) {
						drivers[j]->addService(services[i]); // Add service to driver history
						break;
					}
				}

				for (int j = 0; j < vehicleCount; j++) {
					if (vehicles[j]->getVehicleId() == services[i]->getVehicleId()) {
						vehicles[j]->addService(services[i]); // Add service to vehicle history
						break;
					}
				}

				// Get driver and vehicle rankings from customer
				float driverRanking, vehicleRanking;
				cout << "Enter Driver Ranking (0 to 5): ";
				cin >> driverRanking;
				cout << "Enter Vehicle Ranking (0 to 5): ";
				cin >> vehicleRanking;

				// Update rankings for the correct driver and vehicle
				for (int j = 0; j < driverCount; j++) {
					if (drivers[j]->getDriverId() == services[i]->getDriverId()) {
						drivers[j]->setDriverRanking(driverRanking);  // Update driver ranking
						break;
					}
				}

				for (int j = 0; j < vehicleCount; j++) {
					if (vehicles[j]->getVehicleId() == services[i]->getVehicleId()) {
						vehicles[j]->setOverallRanking(vehicleRanking);  // Update vehicle ranking
						break;
					}
				}

				// Save updated information to files
				ofstream driverFile("drivers.txt", ios::out);
				if (!driverFile) {
					cout << "Unable to open driver file!" << endl;
					return;
				}
				for (int j = 0; j < driverCount; j++) {
					driverFile << drivers[j]->getDriverId() << " "
						<< drivers[j]->getOverallRanking() << endl;
				}
				driverFile.close();

				ofstream vehicleFile("vehicles.txt", ios::out);
				if (!vehicleFile) {
					cout << "Unable to open vehicle file!" << endl;
					return;
				}
				for (int j = 0; j < vehicleCount; j++) {
					vehicleFile << vehicles[j]->getVehicleId() << " "
						<< vehicles[j]->getOverallRanking() << endl;
				}
				vehicleFile.close();

				ofstream serviceFile("serviceRequests.txt", ios::out);
				if (!serviceFile) {
					cout << "Unable to open service file!" << endl;
					return;
				}
				for (int j = 0; j < serviceCount; j++) {
					serviceFile << services[j]->getId() << " "
						<< services[j]->getCustomerId() << " "
						<< services[j]->getVehicleId() << " "
						<< services[j]->getDriverId() << " "
						<< services[j]->getStatus() << endl;
				}
				serviceFile.close();

				cout << "Service completed successfully!" << endl;
				return;
			}
		}

		if (!found) {
			cout << "Service not found!" << endl;
		}
	}


	void printSameVehicleCustomers() {
		int vehicleId;
		cout << "Enter Vehicle ID: ";
		cin >> vehicleId;

		cout << "Customers who used Vehicle ID " << vehicleId << ":" << endl;

		bool found = false;

		// Open the service file and read data
		ifstream serviceFile("serviceRequests.txt");
		if (!serviceFile) {
			cout << "Unable to open service file!" << endl;
			return;
		}


		int serviceId, customerId, vehicleIdInService, driverId;
		bool status;
		while (serviceFile >> serviceId >> customerId >> vehicleIdInService >> driverId >> status) {
			if (vehicleIdInService == vehicleId) {

				ifstream customerFile("customers.txt");
				if (!customerFile) {
					cout << "Unable to open customer file!" << endl;
					return;
				}

				int tempCustomerId;
				string customerName;
				while (customerFile >> tempCustomerId) {
					getline(customerFile, customerName);

					if (tempCustomerId == customerId) {
						cout << "Customer ID: " << tempCustomerId << ", Name: " << customerName << endl;
						found = true;
						break;
					}
				}
				customerFile.close();
			}
		}

		serviceFile.close();

		if (!found) {
			cout << "No customers found for this vehicle." << endl;
		}
	}

	void printDeliveryDriversSameDays() {
		int day, month, year;
		cout << "Enter Date (DD MM YYYY): ";
		cin >> day >> month >> year;

		Date targetDate(day, month, year);

		cout << "Delivery drivers who completed services on " << targetDate << ":" << endl;

		bool found = false;

		// Open the service file and read service records
		ifstream serviceFile("serviceRequests.txt");
		if (!serviceFile) {
			cout << "Unable to open service file!" << endl;
			return;
		}


		int serviceId, customerId, vehicleId, driverId;
		bool status;
		Date serviceDate;
		while (serviceFile >> serviceId >> customerId >> vehicleId >> driverId >> status) {
			if (status == 2) {

				serviceFile >> serviceDate;


				if (serviceDate == targetDate) {
					// If dates match, open the driver file to display driver details
					ifstream driverFile("drivers.txt");
					if (!driverFile) {
						cout << "Unable to open driver file!" << endl;
						return;
					}

					int tempDriverId;
					string driverName;
					float driverRanking;
					while (driverFile >> tempDriverId) {
						driverFile.ignore();
						getline(driverFile, driverName);
						driverFile >> driverRanking;

						if (tempDriverId == driverId) {
							cout << "Driver ID: " << tempDriverId << ", Name: " << driverName << ", Ranking: " << driverRanking << endl;
							found = true;
							break;
						}
					}
					driverFile.close();
				}
			}
		}

		serviceFile.close();

		if (!found) {
			cout << "No delivery drivers found for this date." << endl;
		}
	}

	void printPendingServicesByDate() {
		int day, month, year;
		cout << "Enter Date (DD MM YYYY): ";
		cin >> day >> month >> year;

		Date targetDate(day, month, year);

		cout << "Pending services on " << targetDate << ":" << endl;

		bool found = false;


		ifstream serviceFile("serviceRequests.txt");
		if (!serviceFile) {
			cout << "Unable to open service file!" << endl;
			return;
		}


		int serviceId, customerId, vehicleId, driverId;
		bool status;
		Date serviceDate;
		while (serviceFile >> serviceId >> customerId >> vehicleId >> driverId >> status) {

			serviceFile >> serviceDate;


			if (!status && serviceDate == targetDate) {

				cout << "Service ID: " << serviceId
					<< ", Customer ID: " << customerId
					<< ", Vehicle ID: " << vehicleId
					<< ", Driver ID: " << driverId
					<< ", Service Date: " << serviceDate << endl;
				found = true;
			}
		}

		serviceFile.close();

		if (!found) {
			cout << "No pending services found for this date." << endl;
		}
	}

	void printPendingServicesByDriver() {
		int driverId;
		cout << "Enter Driver ID: ";
		cin >> driverId;

		cout << "Pending services for Driver ID " << driverId << ":" << endl;

		bool found = false;


		ifstream serviceFile("serviceRequests.txt");
		if (!serviceFile) {
			cout << "Unable to open service file!" << endl;
			return;
		}


		int serviceId, customerId, vehicleId;
		bool status;
		Date serviceDate;
		while (serviceFile >> serviceId >> customerId >> vehicleId >> driverId >> status) {

			serviceFile >> serviceDate;


			if (!status && driverId == driverId) {

				cout << "Service ID: " << serviceId
					<< ", Customer ID: " << customerId
					<< ", Vehicle ID: " << vehicleId
					<< ", Driver ID: " << driverId
					<< ", Service Date: " << serviceDate << endl;
				found = true;
			}
		}

		serviceFile.close();

		if (!found) {
			cout << "No pending services found for this driver." << endl;
		}
	}

	void printCanceledServicesByCustomer() {
		int customerId;
		cout << "Enter Customer ID: ";
		cin >> customerId;

		cout << "Canceled services for Customer ID " << customerId << ":" << endl;

		bool found = false;

		ifstream serviceFile("serviceRequests.txt");
		if (!serviceFile) {
			cout << "Unable to open service file!" << endl;
			return;
		}

		int serviceId, customerIdFromFile, vehicleId, driverId;
		bool status;
		Date serviceDate;

		while (serviceFile >> serviceId >> customerIdFromFile >> vehicleId >> driverId >> status) {

			serviceFile >> serviceDate;


			if (status == true && customerIdFromFile == customerId) {

				cout << "Service ID: " << serviceId
					<< ", Customer ID: " << customerIdFromFile
					<< ", Vehicle ID: " << vehicleId
					<< ", Driver ID: " << driverId
					<< ", Service Date: " << serviceDate << endl;
				found = true;
			}
		}

		serviceFile.close();

		if (!found) {
			cout << "No canceled services found for this customer." << endl;
		}
	}



};

int main() {
	TMS tms;
	int choice;

	do {
		tms.displayMenu();
		cin >> choice;
		cout << endl;

		switch (choice) {
		case 1:
			tms.addCustomer();
			break;

		case 2:
			tms.addDriver();
			break;

		case 3:
			tms.removeDriver();
			break;

		case 4:
			tms.addVehicle();
			break;

		case 5:
			tms.removeVehicle();
			break;

		case 6:
			tms.printAllCustomers();
			break;

		case 7:
			tms.printAllDrivers();
			break;

		case 8:
			tms.printAllVehicles();
			break;

		case 9:
			tms.printVehicleDetails();
			break;

		case 10:
			tms.printCustomerHistory();
			break;

		case 11:
			tms.printDriverHistory();
			break;

		case 12:
			tms.printDriversAboveRanking();
			break;

		case 13:
			tms.printDriversWithMultipleLicenses();
			break;


		case 14:
			tms.updateDriverSalaries();
			break;

		case 15:
			tms.addServiceRequest();
			break;

		case 16:
			tms.cancelBooking();
			break;

		case 17:
			tms.completeService();
			break;

		case 18:
			tms.printSameVehicleCustomers();
			break;

		case 19:
			tms.printDeliveryDriversSameDays();
			break;

		case 20:
			tms.printPendingServicesByDate();
			break;

		case 21:
			tms.printPendingServicesByDriver();
			break;

		case 22:
			tms.printCanceledServicesByCustomer();
			break;

		case 0:
			cout << "Exiting the program..." << endl;
			break;

		default:
			cout << "Invalid choice! Please try again." << endl;
			break;
		}
	} while (choice != 0);


	return 0;
}