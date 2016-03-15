/*! \file sns_position_ik.hpp
 * \brief Basic SNS Position IK solver
 * \author Forrest Rogers-Marcovitz
 */
/*
 *    Copyright 2016 Rethink Robotics
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#ifndef SNS_IK_POSITION_IK
#define SNS_IK_POSITION_IK

#include <memory>
#include <Eigen/Dense>
#include <kdl/chain.hpp>
#include <kdl/chainjnttojacsolver.hpp>
#include <kdl/chainfksolverpos_recursive.hpp>

#include "sns_ik/sns_ik_math_utils.hpp"

namespace sns_ik {

// Forward declare SNS Velocity Base Class
class SNSVelocityIK;
class SNSPositionIK {
  public:
    SNSPositionIK(KDL::Chain chain, std::shared_ptr<SNSVelocityIK> velocity_ik);
    ~SNSPositionIK();

    int CartToJnt(const KDL::JntArray& joint_seed,
                  const KDL::Frame& goal_pose,
                  KDL::JntArray* return_joints,
                  const KDL::Twist& tolerances);

    // TODO: looks like this would require the KDL solvers to be wrapped in smart pointers
    //void setChain(const KDL::Chain chain);
    KDL::Chain getChain() { return m_chain; }

    // TODO: figure out the best way of providing a reference to the velocity IK solver
    inline bool getVelocityIK(std::shared_ptr<SNSVelocityIK>& velocitySolver){
        velocitySolver = m_ikVelSolver;
        return m_ikVelSolver != NULL;
    }
    void setTolerance(double linearTolerance, double angularTolerance);
    void setStepSize(double linearMaxStepSize, double angularMaxStepSize);
    void setSolveTimeParameters(double dt, double maxIterations);

  private:
    KDL::Chain m_chain;
    std::shared_ptr<SNSVelocityIK> m_ikVelSolver;
    KDL::ChainFkSolverPos_recursive m_positionFK;
    KDL::ChainJntToJacSolver m_jacobianSolver;
    double m_linearTolerance;
    double m_angularTolerance;
    double m_linearMaxStepSize;
    double m_angularMaxStepSize;
    double m_maxIterations;
    double m_dt;
};

}  // namespace sns_ikl

#endif
