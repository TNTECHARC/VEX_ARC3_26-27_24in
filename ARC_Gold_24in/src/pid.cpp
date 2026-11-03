#include "pid.h"

class PIDController {
    private:
        double kP = 0.00;
        double kI = 0.00;
        double kD = 0.00;
        double acc_err = 0.00;
        double prev_err = 0.00;

    public:
        PIDController(double kP, double kI, double kD) {
            double kP = kP;
            double kI = kI;
            double kD = kD;
            double acc_err = 0;
            double prev_error = 0;
        }

        double getPID(double error) {
            double proportional = kP * error;
            acc_err += error;
            double integral = acc_err * kI;
            double derivative = kD * (error - prev_err); // Also include deltatime???
            double output = (kP * error) + (kI * integral) + (kD * derivative);
            prev_err = error;
            return output;
        }


};