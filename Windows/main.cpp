#include <winrt/Windows.Security.Credentials.UI.h>
#include <winrt/Windows.Foundation.h>
#include <iostream>

using namespace winrt;
using namespace Windows::Security::Credentials::UI;
using namespace Windows::Foundation;

int main()
{
    init_apartment();

    auto availability = UserConsentVerifier::CheckAvailabilityAsync().get();

    if (availability != UserConsentVerifierAvailability::Available)
        return 2;

    auto result = UserConsentVerifier::RequestVerificationAsync(L"Bekreft identitet").get();

    if (result == UserConsentVerificationResult::Verified)
        return 0;
    else
        return 1;
}
