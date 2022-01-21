// Copyright (C) 2021 Intel Corporation
// SPDX-License-Identifier: Apache-2.0
//

#pragma once

#include "cuda_operation_base.hpp"
#include "kernels/interpolate.hpp"
#include "ngraph/op/interpolate.hpp"

namespace CUDAPlugin {

class InterpolateOp : public OperationBase {
public:
    using NodeOp = ngraph::op::v4::Interpolate;
    InterpolateOp(const CreationContext& context,
                  const NodeOp& stridedSliceOp,
                  IndexCollection&& inputIds,
                  IndexCollection&& outputIds);
    void Execute(const InferenceRequestContext& context,
                 Inputs inputs,
                 Outputs outputs,
                 const Workbuffers& workbuffers) const override;

    WorkbufferRequest GetWorkBufferRequest() const override;
    void InitSharedImmutableWorkbuffers(const Buffers& buffers) override;

private:
    std::vector<std::size_t> in_strides_;
    std::vector<std::size_t> out_strides_;
    std::vector<float> scales_;
    std::vector<std::size_t> in_shape_;
    std::vector<std::size_t> out_shape_;
    bool can_use_upscale_optimizing_;

    std::optional<kernel::Interpolate> interpolate_;
};

}  // namespace CUDAPlugin
