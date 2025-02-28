// Copyright (c) 2022, NVIDIA CORPORATION & AFFILIATES. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <vector>
#include <memory>

#include "dali/operators/decoder/video/video_decoder_base.h"
#include "dali/operators/reader/loader/video/frames_decoder_gpu.h"

#ifndef DALI_OPERATORS_DECODER_VIDEO_VIDEO_DECODER_MIXED_H_
#define DALI_OPERATORS_DECODER_VIDEO_VIDEO_DECODER_MIXED_H_

namespace dali {

class VideoDecoderMixed: public VideoDecoderBase<MixedBackend, FramesDecoderGpu> {
  using VideoDecoderBase::DecodeSample;
  using VideoDecoderBase::num_threads_;

 public:
  explicit VideoDecoderMixed(const OpSpec &spec):
    VideoDecoderBase(spec),
    thread_pool_(num_threads_,
                 spec.GetArgument<int>("device_id"),
                 spec.GetArgument<bool>("affine"),
                 "mixed video decoder") {}

  void Run(Workspace &ws) override;

  bool SetupImpl(std::vector<OutputDesc> &output_desc,
                 const Workspace &ws) override;

 private:
  ThreadPool thread_pool_;
};

}  // namespace dali

#endif  // DALI_OPERATORS_DECODER_VIDEO_VIDEO_DECODER_MIXED_H_
