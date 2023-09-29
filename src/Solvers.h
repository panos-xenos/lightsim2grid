// Copyright (c) 2020, RTE (https://www.rte-france.com)
// See AUTHORS.txt
// This Source Code Form is subject to the terms of the Mozilla Public License, version 2.0.
// If a copy of the Mozilla Public License, version 2.0 was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.
// SPDX-License-Identifier: MPL-2.0
// This file is part of LightSim2grid, LightSim2grid implements a c++ backend targeting the Grid2Op platform.

#include "BaseNRSolver.h"
#include "BaseNRSolverSingleSlack.h"
#include "DCSolver.h"
#include "BaseFDPFSolver.h"

#include "SparseLUSolver.h"
#include "KLUSolver.h"
#include "NICSLUSolver.h"
#include "CKTSOSolver.h"

/** Solver based on Newton Raphson, using the SparseLU decomposition of Eigen**/
typedef BaseNRSolver<SparseLULinearSolver> SparseLUSolver;
/** Solver based on Newton Raphson, using the SparseLU decomposition of Eigen, do not consider multiple slack bus**/
typedef BaseNRSolverSingleSlack<SparseLULinearSolver> SparseLUSolverSingleSlack;
/** Solver based on Newton Raphson, using the SparseLU decomposition of Eigen, only suitable for the DC approximation**/
typedef BaseDCSolver<SparseLULinearSolver> DCSolver;
/** Solver based on Fast Decoupled, using the SparseLU decomposition of Eigen**/
typedef BaseFDPFSolver<SparseLULinearSolver> FDPF_SparseLUSolver;

#ifdef KLU_SOLVER_AVAILABLE
    /** Solver based on Newton Raphson, using the KLU linear solver**/
    typedef BaseNRSolver<KLULinearSolver> KLUSolver;
    /** Solver based on Newton Raphson, using the KLU linear solver, do not consider multiple slack bus**/
    typedef BaseNRSolverSingleSlack<KLULinearSolver> KLUSolverSingleSlack;
    /** Solver based on Newton Raphson, using the KLU linear solver, only suitable for the DC approximation**/
    typedef BaseDCSolver<KLULinearSolver> KLUDCSolver;
    /** Solver based on Fast Decoupled, using the KLU linear solver**/
    typedef BaseFDPFSolver<KLULinearSolver> FDPF_KLUSolver;
#elif defined(_READ_THE_DOCS)
    // hack to display accurately the doc in read the doc even if the models are not compiled
    /** Solver based on Newton Raphson, using the KLU linear solver**/
    class KLUSolver : public SparseLUSolver {};
    /** Solver based on Newton Raphson, using the KLU linear solver, do not consider multiple slack bus**/
    class KLUSolverSingleSlack : public SparseLUSolverSingleSlack {};
    /** Solver based on Newton Raphson, using the KLU linear solver, only suitable for the DC approximation**/
    class KLUDCSolver : public DCSolver {};
    /** Solver based on Fast Decoupled, using the KLU linear solver**/
    class FDPF_KLUSolver : public FDPF_SparseLUSolver {};
#endif  // KLU_SOLVER_AVAILABLE

#ifdef NICSLU_SOLVER_AVAILABLE
    /** Solver based on Newton Raphson, using the NICSLU linear solver (needs a specific license)**/
    typedef BaseNRSolver<NICSLULinearSolver> NICSLUSolver;
    /** Solver based on Newton Raphson, using the NICSLU linear solver (needs a specific license), do not consider multiple slack bus**/
    typedef BaseNRSolverSingleSlack<NICSLULinearSolver> NICSLUSolverSingleSlack;
    /** Solver based on Newton Raphson, using the NICSLU linear solver (needs a specific license), only suitable for the DC approximation**/
    typedef BaseDCSolver<NICSLULinearSolver> NICSLUDCSolver;
    /** Solver based on Fast Decoupled, using the NICSLU linear solver (needs a specific license)**/
    typedef BaseFDPFSolver<NICSLULinearSolver> FDPF_NICSLUSolver;
#elif defined(_READ_THE_DOCS)
    // hack to display accurately the doc in read the doc even if the models are not compiled
    /** Solver based on Newton Raphson, using the NICSLU linear solver (needs a specific license)**/
    class NICSLUSolver : public SparseLUSolver{};
    /** Solver based on Newton Raphson, using the NICSLU linear solver (needs a specific license), do not consider multiple slack bus**/
    class NICSLUSolverSingleSlack : public SparseLUSolverSingleSlack{};
    /** Solver based on Newton Raphson, using the NICSLU linear solver (needs a specific license), only suitable for the DC approximation**/
    class NICSLUDCSolver : public DCSolver{};
    /** Solver based on Fast Decoupled, using the NICSLU linear solver (needs a specific license)**/
    class FDPF_NICSLUSolver : public FDPF_SparseLUSolver {};
#endif  // NICSLU_SOLVER_AVAILABLE

#ifdef CKTSO_SOLVER_AVAILABLE
    /** Solver based on Newton Raphson, using the CKTSO linear solver (needs a specific license)**/
    typedef BaseNRSolver<CKTSOLinearSolver> CKTSOSolver;
    /** Solver based on Newton Raphson, using the CKTSO linear solver (needs a specific license), do not consider multiple slack bus**/
    typedef BaseNRSolverSingleSlack<CKTSOLinearSolver> CKTSOSolverSingleSlack;
    /** Solver based on Newton Raphson, using the CKTSO linear solver (needs a specific license), only suitable for the DC approximation**/
    typedef BaseDCSolver<CKTSOLinearSolver> CKTSODCSolver;
    /** Solver based on Fast Decoupled, using the CKTSO linear solver (needs a specific license)**/
    typedef BaseFDPFSolver<CKTSOLinearSolver> FDPF_CKTSOSolver;
#elif defined(_READ_THE_DOCS)
    // hack to display accurately the doc in read the doc even if the models are not compiled
    /** Solver based on Newton Raphson, using the CKTSO linear solver (needs a specific license)**/
    class CKTSOSolver : public SparseLUSolver{};
     /** Solver based on Newton Raphson, using the CKTSO linear solver (needs a specific license), do not consider multiple slack bus**/
    class CKTSOSolverSingleSlack : public SparseLUSolverSingleSlack{};
    /** Solver based on Newton Raphson, using the CKTSO linear solver (needs a specific license), only suitable for the DC approximation**/
    class CKTSODCSolver : public DCSolver{};
    /** Solver based on Fast Decoupled, using the CKTSO linear solver (needs a specific license)**/
    class FDPF_CKTSOSolver : public FDPF_SparseLUSolver {};
#endif  // CKTSO_SOLVER_AVAILABLE
