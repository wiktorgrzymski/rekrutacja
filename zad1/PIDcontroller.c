/**
 * @file main.c
 * @brief Simple PID Controller Simulation
 */

#include <stdio.h>
#include <math.h>

/**
 * @struct PIDController
 * @brief Structure representing a PID controller
 */
typedef struct
{
    double Kp;        /**< Proportional Gain */
    double Ki;        /**< Integral Gain */
    double Kd;        /**< Derivative Gain */
    double deltaT;    /**< Time Step */
    double setpoint;  /**< Desired Setpoint */
    double integral;  /**< Integral Value */
    double prevError; /**< Previous Error */
} PIDController;

/**
 * @brief Initialize the PID controller with given parameters.
 * @param controller Pointer to the PID controller to be initialized.
 * @param Kp Proportional Gain.
 * @param Ki Integral Gain.
 * @param Kd Derivative Gain.
 * @param deltaT Time Step.
 * @param setpoint Desired Setpoint.
 */
void initPIDController(PIDController *controller, double Kp, double Ki, double Kd, double deltaT, double setpoint)
{
    controller->Kp = Kp;
    controller->Ki = Ki;
    controller->Kd = Kd;
    controller->deltaT = deltaT;
    controller->setpoint = setpoint;
    controller->integral = 0.0;
    controller->prevError = 0.0;
}

/**
 * @brief Update the PID controller with new process variable and time.
 * @param controller Pointer to the PID controller to be updated.
 * @param processVariable Current process variable.
 * @param time Current time.
 * @return Control output.
 */
double updatePIDController(PIDController *controller, double processVariable, double time)
{
    // Calculate the error based on the control object equation
    double error = controller->setpoint - (1 - exp(-time / 10.0));

    // Calculate PID components
    double P = controller->Kp * error;
    

    // Calculate the integral component using the trapezoidal rule
    double integralIncrement = (error + controller->prevError) * controller->deltaT / 2.0;
    controller->integral += controller->Ki * integralIncrement;

    double D = controller->Kd * (error - controller->prevError) / controller->deltaT;
    
    // Limit the integral to prevent excessive windup
    if (controller->integral > 5.0)
    {
        controller->integral = 5.0;
    }
    else if (controller->integral < -5.0)
    {
        controller->integral = -5.0;
    }

    // Calculate the control output
    double controlOutput = P + controller->integral + D;

    // Limit the control output to the range of -5 to 5
    if (controlOutput > 5.0)
    {
        controlOutput = 5.0;
    }
    else if (controlOutput < -5.0)
    {
        controlOutput = -5.0;
    }

    // Update the previous error
    controller->prevError = error;

    return controlOutput;
}

/**
 * @brief Calculate the process variable based on the control object equation.
 * @param time Current time.
 * @return Calculated process variable.
 */
double calculateProcessVariable(double time)
{
    return 1 - exp(-time / 10.0);
}

/**
 * @brief Main function for the PID controller simulation.
 * @return 0 on successful execution.
 */
int main()
{
    // Example usage of the PID controller with adjusted parameters
    PIDController controller;
    initPIDController(&controller, 1.0, 0.0, 0.02, 0.1, 1.0); // Adjust Kp, Ki, and Kd here

    double time = 0.0;
    double processVariable = 0.0;
    double controlOutput = 0.0;
    double totalSimTime = 100.0;
    int iterations = 0;

    // Simulate the control process
    while (time <= totalSimTime)
    {

        // Update the process variable
        processVariable = calculateProcessVariable(time);

        // Update the control output
        controlOutput = updatePIDController(&controller, processVariable, time);

        // Update the time
        time += controller.deltaT;

        // Display the results
        printf("Time: %lf, No PID: %lf, PID: %lf\n", time, processVariable, processVariable + controlOutput);

        // Increment the iterations
        iterations++;
    }

    // Final message
    printf("Simulation completed in %d iterations.\n", iterations);

    return 0;
}
