import Foundation
import LocalAuthentication

let context = LAContext()
var error: NSError?

if context.canEvaluatePolicy(.deviceOwnerAuthentication, error: &error) {
    context.evaluatePolicy(.deviceOwnerAuthentication, localizedReason: "Bekreft identitet") { success, error in
        exit(success ? 0 : 1)
    }

    RunLoop.main.run()
} else {
    exit(2) // No biometrics or password fallback available
}
