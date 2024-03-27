// Copyright 2022-2023 Google LLC
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

#ifndef THIRD_PARTY_NEARBY_SHARING_PAIRED_KEY_VERIFICATION_RUNNER_H_
#define THIRD_PARTY_NEARBY_SHARING_PAIRED_KEY_VERIFICATION_RUNNER_H_

#include <stdint.h>

#include <functional>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "absl/strings/string_view.h"
#include "absl/time/time.h"
#include "internal/platform/clock.h"
#include "internal/platform/device_info.h"
#include "proto/sharing_enums.pb.h"
#include "sharing/certificates/nearby_share_certificate_manager.h"
#include "sharing/certificates/nearby_share_decrypted_public_certificate.h"
#include "sharing/incoming_frames_reader.h"
#include "sharing/nearby_connection.h"
#include "sharing/nearby_sharing_settings.h"
#include "sharing/proto/enums.pb.h"
#include "sharing/proto/wire_format.pb.h"

namespace nearby {
namespace sharing {

class PairedKeyVerificationRunner
    : public std::enable_shared_from_this<PairedKeyVerificationRunner> {
 public:
  enum class PairedKeyVerificationResult {
    // Default value for verification result.
    kUnknown,
    // Succeeded with verification.
    kSuccess,
    // Failed to verify.
    kFail,
    // Unable to verify. Occurs when missing proper certificates.
    kUnable,
  };

  PairedKeyVerificationRunner(
      Clock* clock, DeviceInfo& device_info, int64_t share_target_id,
      bool share_target_is_incoming, proto::DeviceVisibility visibility,
      proto::DeviceVisibility last_visibility, absl::Time last_visibility_time,
      absl::string_view endpoint_id, const std::vector<uint8_t>& token,
      NearbyConnection* connection,
      const std::optional<NearbyShareDecryptedPublicCertificate>& certificate,
      NearbyShareCertificateManager* certificate_manager,
      IncomingFramesReader* frames_reader, absl::Duration read_frame_timeout);

  ~PairedKeyVerificationRunner();

  void Run(std::function<
           void(PairedKeyVerificationResult verification_result,
                ::location::nearby::proto::sharing::OSType remote_os_type)>
               callback);

  std::weak_ptr<PairedKeyVerificationRunner> GetWeakPtr() {
    return this->weak_from_this();
  }

 private:
  void SendPairedKeyEncryptionFrame();
  void OnReadPairedKeyEncryptionFrame(
      std::optional<nearby::sharing::service::proto::V1Frame> frame);
  void OnReadPairedKeyResultFrame(
      std::vector<PairedKeyVerificationResult> verification_results,
      std::optional<nearby::sharing::service::proto::V1Frame> frame);
  void SendPairedKeyResultFrame(PairedKeyVerificationResult result);
  PairedKeyVerificationResult VerifyRemotePublicCertificate(
      const nearby::sharing::service::proto::V1Frame& frame);
  PairedKeyVerificationResult VerifyRemotePublicCertificateRelaxed(
      const nearby::sharing::service::proto::V1Frame& frame);
  PairedKeyVerificationResult
  VerifyRemotePublicCertificateWithPrivateCertificate(
      proto::DeviceVisibility visibility,
      const nearby::sharing::service::proto::V1Frame& frame);
  PairedKeyVerificationResult VerifyPairedKeyEncryptionFrame(
      const nearby::sharing::service::proto::V1Frame& frame);
  PairedKeyVerificationResult MergeResults(
      const std::vector<PairedKeyVerificationResult>& results);
  bool RelaxRestrictToContactsIfNeeded() const;

  nearby::Clock* const clock_;
  nearby::DeviceInfo& device_info_;
  const int64_t share_target_id_;
  proto::DeviceVisibility visibility_;
  proto::DeviceVisibility last_visibility_;
  absl::Time last_visibility_time_;
  std::string endpoint_id_;
  std::vector<uint8_t> raw_token_;
  NearbyConnection* connection_;
  std::optional<NearbyShareDecryptedPublicCertificate> certificate_;
  NearbyShareCertificateManager* certificate_manager_;
  IncomingFramesReader* frames_reader_;
  const absl::Duration read_frame_timeout_;
  std::function<void(PairedKeyVerificationResult,
                     ::location::nearby::proto::sharing::OSType)>
      callback_;
  bool relax_restrict_to_contacts_ = false;

  char local_prefix_;
  char remote_prefix_;
};

}  // namespace sharing
}  // namespace nearby

#endif  // THIRD_PARTY_NEARBY_SHARING_PAIRED_KEY_VERIFICATION_RUNNER_H_
