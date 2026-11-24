#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class LaunchpadAsset {
protected:
    string padID;
    bool isArmed;

public:
    static int activeLaunchpads;

    LaunchpadAsset(string id) : padID(id), isArmed(true) {
        activeLaunchpads++;
    }

    virtual ~LaunchpadAsset() {
        activeLaunchpads--;
    }

    virtual void runLaunchChecklist() = 0;
};

int LaunchpadAsset::activeLaunchpads = 0;

class CryoFuelModule : virtual public LaunchpadAsset {
protected:
    double fuelPressureBar;

public:
    CryoFuelModule(string id, double pressure) : LaunchpadAsset(id), fuelPressureBar(pressure) {}

    void checkCryoFuel() {
        cout << "Cryo fuel line [" << padID << "] tank pressure: " << fuelPressureBar << " bar." << endl;
    }
};

class IgnitionControlModule : virtual public LaunchpadAsset {
protected:
    double igniterTempCelsius;

public:
    IgnitionControlModule(string id, double temp) : LaunchpadAsset(id), igniterTempCelsius(temp) {}

    void checkIgnition() {
        cout << "Ignition system [" << padID << "] chamber baseline: " << igniterTempCelsius << " C." << endl;
    }
};

class OrbitalLaunchComplex : public CryoFuelModule, public IgnitionControlModule {
private:
    double payloadMassTons;

public:
    OrbitalLaunchComplex(string id, double pressure, double temp, double payload)
        : LaunchpadAsset(id),
          CryoFuelModule(id, pressure),
          IgnitionControlModule(id, temp),
          payloadMassTons(payload) {}

    ~OrbitalLaunchComplex() {
        cout << "Launchpad " << padID << " safed and umbilical towers retracted." << endl;
    }

    void runLaunchChecklist() override {
        cout << "\n--- Orbital Launchpad Telemetry Report: " << padID << " ---" << endl;
        checkCryoFuel();
        checkIgnition();
        cout << "Payload Mass Onboard: " << fixed << setprecision(1) << payloadMassTons << " Tons" << endl;
        cout << "Launch Status: Go for Ignition" << endl;
    }
};

int main() {
    LaunchpadAsset* pad = new OrbitalLaunchComplex("PAD-LC39A", 245.5, 22.4, 63.8);

    pad->runLaunchChecklist();

    cout << "\nActive Launchpad Complexes: " << LaunchpadAsset::activeLaunchpads << endl;

    delete pad;

    cout << "Active Complexes After Liftoff: " << LaunchpadAsset::activeLaunchpads << endl;

    return 0;
}
