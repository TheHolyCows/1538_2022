


// double CowRobot::GetDriveDistance()
// {
//     float direction = -1.0;
//     float position = 0;
//     if (m_LeftDriveA)
//     {
//         // position / falcon units per rev * gear ratio
//         position = m_LeftDriveA->GetPosition() / (2048 * (46 / 12));
//         position *= 12.56636;
//         position *= direction;
//     }
//     return position;
// }

// bool CowRobot::DriveDistance(double distance)
// {
//     double PID_P = CONSTANT("DRIVE_P");
//     double PID_D = CONSTANT("DRIVE_D");
//     double error = distance - GetDriveDistance();
//     double dError = error - m_PreviousDriveError;
//     double output = PID_P * error + PID_D * dError;

//     double speed = CONSTANT("PTO_DRIVE_SPEED");
//     DriveLeftRight(speed - output, speed + output);

//     m_PreviousDriveError = error;

//     return (fabs(error) < 4 && CowLib::UnitsPerSecond(fabs(dError)) < 1);
// }

// bool CowRobot::DriveDistanceWithHeading(double heading, double distance, double speed)
// {
//     double PID_P = CONSTANT("DRIVE_P");
//     double PID_D = CONSTANT("DRIVE_D");
//     double error = distance - GetDriveDistance();
//     double dError = error - m_PreviousDriveError;
//     double output = PID_P * error + PID_D * dError;

//     double throttle = CowLib::LimitMix(output, speed);
//     // throttle *= -1;
//     // std::cout << "Drive request speed: " << throttle << std::endl;

//     bool headingResult = DriveWithHeading(heading, throttle);

//     m_PreviousDriveError = error;

//     return (fabs(error) < 4 && headingResult);
// }

// bool CowRobot::TurnToHeading(double heading)
// {
//     double PID_P = CONSTANT("TURN_P");
//     double PID_D = CONSTANT("TURN_D");
//     double error = m_Gyro->GetAngle() - heading;
//     double dError = error - m_PreviousGyroError;
//     double output = PID_P * error + PID_D * dError;

//     // speed *= -speed;

//     DriveLeftRight(-output, output);

//     m_PreviousGyroError = error;

//     return (fabs(error) < 1 && CowLib::UnitsPerSecond(fabs(dError)) < 0.5);
// }

// bool CowRobot::DriveWithHeading(double heading, double speed)
// {
//     double PID_P = CONSTANT("TURN_P");
//     double PID_D = CONSTANT("TURN_D");
//     double error = m_Gyro->GetAngle() - heading;
//     double dError = error - m_PreviousGyroError;
//     double output = PID_P * error + PID_D * dError;

//     // speed *= -speed;

//     DriveLeftRight(speed - output, speed + output);

//     m_PreviousGyroError = error;

//     return (fabs(error) < 1 && CowLib::UnitsPerSecond(fabs(dError)) < 0.5);
// }

// bool CowRobot::DriveWithHeading(double heading, double speed, double maxSpeed)
// {
//     double PID_P = CONSTANT("TURN_P");
//     double PID_D = CONSTANT("TURN_D");
//     double error = heading - m_Gyro->GetAngle();
//     double dError = error - m_PreviousGyroError;
//     double output = PID_P * error + PID_D * dError;
//     output = CowLib::LimitMix(output, maxSpeed);

//     DriveLeftRight(speed + output, speed - output);

//     m_PreviousGyroError = error;

//     return (fabs(error) < 1 && CowLib::UnitsPerSecond(fabs(dError)) < 0.5);
// }

// void CowRobot::DriveSpeedTurn(float speed, float turn, bool quickTurn)
// {
//     // Linear degredation of steeering based off of velocity

//     // velocity *= 0.003;
//     float temp_vel = speed;
//     float sensitivity = 0;

//     if (temp_vel < 0)
//         temp_vel = -temp_vel;

//     // printf("Velocity: %f, stick: %f\r\n", velocity, temp_vel);

//     if (speed < 0.10 && speed > -0.10)
//         speed = 0;
//     if (((turn < 0.02) && (turn > -0.02)) || ((speed == 0) && !quickTurn))
//         turn = 0;

//     if (quickTurn)
//     {
//         if (speed == 0.0)
//         {
//             sensitivity = 1;
//         }
//         else
//         {
//             sensitivity = CONSTANT("STEERING_QUICKTURN");
//         }
//     }
//     else
//     {
//         sensitivity = CONSTANT("STEERING_NOQUICKTURN");
//     }

//     turn *= sensitivity;
//     // turn = -turn;

//     float left_power = CowLib::LimitMix(speed - turn);
//     float right_power = CowLib::LimitMix(speed + turn);

//     DriveLeftRight(left_power, right_power);
// }

// // Allows robot to spin in place
// void CowRobot::QuickTurn(float turnRate)
// {
//     // When provided with + turn, quick turn right

//     float left = -1 * turnRate;
//     float right = turnRate;

//     DriveLeftRight(left, right);
// }