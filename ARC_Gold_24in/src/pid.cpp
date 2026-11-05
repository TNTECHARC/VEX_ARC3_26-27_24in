#include "pid.h"
/// @brief This class is used to calculate PID values for the motors
class PIDController {
    private:
        double kP = 0.00;
        double kI = 0.00;
        double kD = 0.00;
        double settleRange = 0.01;
        double acc_err = 0.00;
        double prev_err = 0.00;

    public:

        /// @brief Constructor for the PIDController class
        /// @param kP Represents tuning value for P
        /// @param kI Represents tuning value for I
        /// @param kD Represents tuning value for D
        PIDController(double kP, double kI, double kD, double settleRange) {
            this->kP = kP;
            this->kI = kI;
            this->kD = kD;
            this->settleRange = settleRange;
        }

        /// @brief Calculates a single pid number
        /// using proportional, integral, and derivative values
        /// @param error The error between the actual rotation value and the predicted
        /// @return A double representing the single calculated PID value
        double getPID(double error) {
            acc_err += error;
            double integral = acc_err * kI;
            double derivative = kD * (error - prev_err);
            double output = (kP * error) + (kI * integral) + (kD * derivative);
            prev_err = error;
            return output;
        }
        
        /// @brief Determines if the motor has settled to not infinitely slow down and timeout
        /// @param error The error between the actual rotation value and the predicted
        /// @return A boolean representing if the motor is settled or not
        double isSettled(double error) {
            // If it is close to zero, then timeout
            if (error <= settleRange && error >= -(settleRange))
                return true;
            return false;
        }

};