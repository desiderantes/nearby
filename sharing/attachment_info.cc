// Copyright 2022 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "sharing/attachment_info.h"

namespace nearby::sharing {

AttachmentInfo::AttachmentInfo() = default;
AttachmentInfo::~AttachmentInfo() = default;

AttachmentInfo::AttachmentInfo(const AttachmentInfo&) = default;
AttachmentInfo& AttachmentInfo::operator=(const AttachmentInfo&) = default;
AttachmentInfo::AttachmentInfo(AttachmentInfo&&) = default;
AttachmentInfo& AttachmentInfo::operator=(AttachmentInfo&&) = default;

}  // namespace nearby::sharing
