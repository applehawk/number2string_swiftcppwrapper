//
//  SwiftExtensions.swift
//  NumberConverterSwift
//
//  Created by Teller.Vlad on 15.05.16.
//  Copyright © 2016 Teller.Vlad. All rights reserved.
//

import UIKit

extension String {
    //Predefine KEY = VALUE; in Localizable.strings
    func localized( key : String ) -> String {
        return NSLocalizedString(key, tableName: nil, bundle: NSBundle.mainBundle(), value: self, comment: self)
    }
    
    func localized() -> String {
        return NSLocalizedString(self, tableName: nil, bundle: NSBundle.mainBundle(), value: "", comment: "")
    }
    
    func localizedPlural(argument: CVarArgType) -> String {
        return NSString.localizedStringWithFormat(localized(), argument) as String
    }
    
    init(htmlEncodedString: String) {
        let encodedData = htmlEncodedString.dataUsingEncoding(NSUTF8StringEncoding)
        let attributedOptions : [String: AnyObject] = [
            NSDocumentTypeDocumentAttribute: NSHTMLTextDocumentType,
            NSCharacterEncodingDocumentAttribute: NSUTF8StringEncoding
        ]
        
        if let encodedData = encodedData, let attributedString = try? NSAttributedString(data: encodedData, options: attributedOptions, documentAttributes: nil)
        {
            self.init(attributedString.string)
        } else {
            self.init(htmlEncodedString)
        }
        
    }
}