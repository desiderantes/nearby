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

#include "fastpair/client/windows/fast_pair_controller_adapter.h"

namespace location {
namespace nearby {
namespace fastpair {

FastPairController *InitFastPairController() {
  return new FastPairController();
}

void CloseFastPairController(FastPairController *pController) {
  if (pController != nullptr) delete pController;
}

void StartScanning(FastPairController *pController) {
}

void ServerAccess(FastPairController *pController) {
}

}  // namespace fastpair
}  // namespace nearby
}  // namespace location