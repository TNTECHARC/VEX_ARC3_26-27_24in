#include "pid.h"

class PIDController {
    private:
        double kP = 0.00;
        double kI = 0.00;
        double kD = 0.00;

    public:
        PIDController(double kP, double kI, double kD) {
            double kP = kP;
            double kI = kI;
            double kD = kD;
        }

        double getPID(double error) {
            double proportional = kP * error;
            double integral
        }


}