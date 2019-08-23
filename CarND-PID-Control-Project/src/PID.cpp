#include "PID.h"

#include <iostream>
#include <cmath>
#include <vector>
#include <numeric>
#include <algorithm>

using std::vector;
using std::accumulate;
using std::numeric_limits;
using std::cout;
using std::endl;

/**
 * TODO: Complete the PID class. You may add any additional desired functions.
 */

PID::PID() {}

PID::~PID() {}

void PID::Init(vector<double> tau, vector<double> gd, int timestep){
  /**
   * TODO: Initialize PID coefficients (and errors, if needed)
   */
  this->_cte = {0, 0, 0};
  this->_tau = tau;
  this->_gd = gd;
  this->counter = 1;
  this->twiddle_timestep = timestep;
  this->do_twiddle = false;
  this->total_error = 0.0;
  this->best_error = numeric_limits<float>::max();
}

void PID::UpdateError(double cte){
  /**
   * TODO: Update PID errors based on cte.
   */
  this->_cte[1] = cte - this->_cte[0];
  this->_cte[0] = cte;
  this->_cte[2] += cte;
  this->total_error += cte*cte;
  if ((this->counter % this->twiddle_timestep) == 0) this->do_twiddle = true;
  else this->do_twiddle = false;
}

float PID::TotalError(){
  /**
   * TODO: Calculate and return the total error
   */
  float error = -this->_tau[0]*this->_cte[0] - this->_tau[1]*this->_cte[1] - this->_tau[2]*this->_cte[2];
  return error;  // TODO: Add your total error calc here!
}

float PID::Twiddle(double tol, double rate){
  float total_error = this->total_error/ this->counter; 
  if (this->do_twiddle == true){
    cout << "Best error: " << total_error << " | " << this->_gd[0] + this->_gd[1] + this->_gd[2] << " | tau: "
          << this->_tau[0] << ", " << this->_tau[1] << ", " << this->_tau[2] << " | gd: "
          << this->_gd[0] << ", " << this->_gd[1] << ", " << this->_gd[2] << endl;
    while (accumulate(_gd.begin(), _gd.end(), 0.0) > tol){
      for (unsigned int i=0; i < _cte.size(); i++){
        // increase tau
        this->_tau[i] += this->_gd[i];
        // Check currently if total error is less than best error
        if (total_error < this->best_error){
          this->best_error = total_error;
          this->_gd[i] *= (1.0 + rate);
        }
        // else reset the tau and incre or decre the tau and gd depending on if total error is still greater than best error
        else {
          this->_tau[i] -= 2*this->_gd[i];

          if (total_error < this->best_error){
            this->best_error = total_error;
            this->_gd[i] *= (1.0 + rate);
          }
          else {
            this->_tau[i] += this->_gd[i];
            this->_gd[i] *= (1.0 - rate);
          }
        }
      }
    }

    this->counter = 0;
    this->total_error = 0;
    cout << "Final -- Best error: " << this->best_error << " | tau: "
          << this->_tau[0] << ", " << this->_tau[1] << ", " << this->_tau[2] << " | gd: "
          << this->_gd[0] << ", " << this->_gd[1] << ", " << this->_gd[2] << endl;
    return TotalError();
  }
  else {
    return TotalError();
  }
}